static PConstant base_p = 1;
static SensorVal base_tolerance = 10;

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
    config.p_constant = base_p;
    config.tolerance = base_tolerance;
    run_control(&config);
}

task base_right_controller() {
    PControlConfig config;
    config.control = &base_right_control;
    config.motor_power = &base_right_power;
    config.current_value = &base_right_encoder;
    config.p_constant = base_p;
    config.tolerance = base_tolerance;
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
