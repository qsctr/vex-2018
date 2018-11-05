PIDConstant base_p = 1;
PIDConstant base_i = 0;
PIDConstant base_d = 0;
SensorVal base_i_range = 100;
SensorVal base_tolerance = 10;
MotorPower base_min_power = 0;

void reset_base_encoders() {
    resetMotorEncoder(base_left2);
    resetMotorEncoder(base_right2);
}

PControl base_left_control;
PControl base_right_control;

task base_left_controller() {
    PControlConfig config;
    config.control = &base_left_control;
    config.motor_power = &base_left_power;
    config.current_value = &base_left_encoder;
    config.p_constant = &base_p;
    config.i_constant = &base_i;
    config.d_constant = &base_d;
    config.i_range = &base_i_range;
    config.tolerance = &base_tolerance;
    config.min_power = &base_min_power;
    run_control(&config);
}

task base_right_controller() {
    PControlConfig config;
    config.control = &base_right_control;
    config.motor_power = &base_right_power;
    config.current_value = &base_right_encoder;
    config.p_constant = &base_p;
    config.i_constant = &base_i;
    config.d_constant = &base_d;
    config.i_range = &base_i_range;
    config.tolerance = &base_tolerance;
    config.min_power = &base_min_power;
    run_control(&config);
}

void drive(SensorVal left_target, SensorVal right_target) {
    reset_base_encoders();
    set_control(&base_left_control, left_target);
    set_control(&base_right_control, right_target);
    while (!(base_left_control.on_target && base_right_control.on_target)) {
        sleep(LOOP_PERIOD);
    }
}
