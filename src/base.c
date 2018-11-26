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
PIDControlConfig base_left_control_config;
PIDControlConfig base_right_control_config;

void init_base() {
    base_left_control_config.control = &base_left_control;
    base_left_control_config.motor_power = &base_left_power;
    base_left_control_config.current_value = &base_left_encoder;
    base_left_control_config.p_constant = &base_p;
    base_left_control_config.i_constant = &base_i;
    base_left_control_config.d_constant = &base_d;
    base_left_control_config.i_range = &base_i_range;
    base_left_control_config.tolerance = &base_tolerance;
    base_left_control_config.min_power = &base_min_power;

    base_right_control_config.control = &base_right_control;
    base_right_control_config.motor_power = &base_right_power;
    base_right_control_config.current_value = &base_right_encoder;
    base_right_control_config.p_constant = &base_p;
    base_right_control_config.i_constant = &base_i;
    base_right_control_config.d_constant = &base_d;
    base_right_control_config.i_range = &base_i_range;
    base_right_control_config.tolerance = &base_tolerance;
    base_right_control_config.min_power = &base_min_power;
}

task base_left_controller() {
    run_control(&base_left_control_config);
}

task base_right_controller() {
    run_control(&base_right_control_config);
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
