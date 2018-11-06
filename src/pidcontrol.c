typedef struct {
    bool enabled;
    PIDSettingIndex pid_index;
    SensorVal target;
    bool on_target;
} PIDControl;

void init_control(PIDControl *c) {
    c->enabled = false;
    c->pid_index = 0;
}

void set_control(PIDControl *c, SensorVal target, PIDSettingIndex pid_index = 0) {
    c->enabled = true;
    c->pid_index = pid_index;
    c->target = target;
    c->on_target = false;
}

void wait_on_target(PIDControl *c) {
    while (!c->on_target) {
        sleep(LOOP_PERIOD);
    }
}

void sync_control(PIDControl *c, SensorVal target, PIDSettingIndex pid_index = 0) {
    set_control(c, target, pid_index);
    wait_on_target(c);
}

void disable_control(PIDControl *c) {
    c->enabled = false;
}

typedef struct {
    PIDConstant *p_constant;
    PIDConstant *i_constant;
    PIDConstant *d_constant;
    SensorVal *i_range;
} PIDSetting;

typedef struct {
    PIDControl *control;
    MotorPower *motor_power;
    SensorVal *current_value;
    PIDSetting **pid_settings;
    SensorVal *tolerance;
    MotorPower *min_power;
} PIDControlConfig;

void run_control(const PIDControlConfig *config) {
    init_control(config->control);
    SensorVal integral;
    SensorVal prev_error;
    while (1) {
        if (config->control->enabled) {
            SensorVal error = config->control->target - *(config->current_value);
            config->control->on_target = abs(error) < *config->tolerance;
            PIDSetting *setting = config->pid_settings + config->control->pid_index;
            if (abs(error) < *setting->i_range) {
                integral += error;
            } else {
                integral = 0;
            }
            SensorVal derivative = error - prev_error;
            prev_error = error;
            SensorVal power = *setting->p_constant * error
                            + *setting->i_constant * integral
                            + *setting->d_constant * derivative;
            if (power > MOTOR_MAX) power = MOTOR_MAX;
            if (power < MOTOR_MIN) power = MOTOR_MIN;
            if (!config->control->on_target) {
                if (power > 0 && power < *config->min_power) power = *config->min_power;
                if (power < 0 && power > -*config->min_power) power = -*config->min_power;
            }
            *config->motor_power = power;
        } else {
            integral = 0;
            prev_error = 0;
        }
        sleep(LOOP_PERIOD);
    }
}
