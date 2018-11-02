typedef struct {
    bool enabled;
    SensorVal target;
    bool on_target;
} PControl;

void init_control(PControl *c) {
    c->enabled = false;
}

void set_control(PControl *c, SensorVal target) {
    c->enabled = true;
    c->target = target;
    c->on_target = false;
}

void wait_on_target(PControl *c) {
    while (!c->on_target) {
        sleep(LOOP_PERIOD);
    }
}

void sync_control(PControl *c, SensorVal target) {
    set_control(c, target);
    wait_on_target(c);
}

void disable_control(PControl *c) {
    c->enabled = false;
}

typedef struct {
    PControl *control;
    MotorPower *motor_power;
    SensorVal *current_value;
    PConstant p_constant;
    SensorVal tolerance;
} PControlConfig;

void run_control(const PControlConfig *config) {
    init_control(config->control);
    while (1) {
        if (config->control->enabled) {
            SensorVal error = config->control->target - *(config->current_value);
            config->control->on_target = abs(error) < config->tolerance;
            SensorVal power = config->p_constant * error;
            if (power > MOTOR_MAX) power = MOTOR_MAX;
            if (power < MOTOR_MIN) power = MOTOR_MIN;
            *(config->motor_power) = power;
        }
        sleep(LOOP_PERIOD);
    }
}
