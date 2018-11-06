PIDConstant base_straight_p = 0.1;
PIDConstant base_straight_i = 0;
PIDConstant base_straight_d = 0;
SensorVal base_straight_i_range = 0;
PIDConstant base_turn_p = 0.2;
PIDConstant base_turn_i = 0;
PIDConstant base_turn_d = 0;
SensorVal base_turn_i_range = 100;
SensorVal base_tolerance = 20;
MotorPower base_min_power = 25;

void reset_base_encoders() {
    resetMotorEncoder(base_left2);
    resetMotorEncoder(base_right2);
}

PControl base_left_control;
PControl base_right_control;

PIDSetting *base_pid_settings[2];
PIDSetting base_straight_setting;
PIDSetting base_turn_setting;

void setup_base() {
    base_pid_settings[0] = &base_straight_setting;
    base_straight_setting.p_constant = &base_straight_p;
    base_straight_setting.i_constant = &base_straight_i;
    base_straight_setting.d_constant = &base_straight_d;
    base_straight_setting.i_range = &base_straight_i_range;
    base_pid_settings[1] = &base_turn_setting;
    base_turn_setting.p_constant = &base_turn_p;
    base_turn_setting.i_constant = &base_turn_i;
    base_turn_setting.d_constant = &base_turn_d;
    base_turn_setting.i_range = &base_turn_i_range;
}

task base_left_controller() {
    PControlConfig config;
    config.control = &base_left_control;
    config.motor_power = &base_left_power;
    config.current_value = &base_left_encoder;
    config.pid_settings = (PIDSetting **) base_pid_settings;
    config.tolerance = &base_tolerance;
    config.min_power = &base_min_power;
    run_control(&config);
}

task base_right_controller() {
    PControlConfig config;
    config.control = &base_right_control;
    config.motor_power = &base_right_power;
    config.current_value = &base_right_encoder;
    config.pid_settings = (PIDSetting **) base_pid_settings;
    config.tolerance = &base_tolerance;
    config.min_power = &base_min_power;
    run_control(&config);
}

void drive(SensorVal left_target, SensorVal right_target) {
    reset_base_encoders();
    PIDSettingIndex ix = (PIDSettingIndex) !(sgn(left_target) == sgn(right_target));
    set_control(&base_left_control, left_target, ix);
    set_control(&base_right_control, right_target, ix);
    while (!(base_left_control.on_target && base_right_control.on_target)) {
        sleep(LOOP_PERIOD);
    }
}
