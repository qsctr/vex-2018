PIDConstant base_p = 0.2;
PIDConstant base_i = 0;
PIDConstant base_d = 1.5;
SensorVal base_i_range = 100;
SensorVal base_tolerance = 10;
MotorPower base_min_power = 25;

void reset_base_encoders() {
    resetMotorEncoder(base_left2);
    resetMotorEncoder(base_right2);
}

PIDControl base_left_control;
PIDControl base_right_control;

task base_left_controller() {
    PIDControlConfig config;
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
    PIDControlConfig config;
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

void drive(SensorVal left_target, SensorVal right_target, Ms time = 0) {
    reset_base_encoders();
    set_control(&base_left_control, left_target);
    set_control(&base_right_control, right_target);
    if (time) {
        sleep(time);
    } else {
        while (!(base_left_control.on_target && base_right_control.on_target)) {
            sleep(LOOP_PERIOD);
        }
    }
}
