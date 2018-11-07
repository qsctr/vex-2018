#define ARM_GROUND 200
#define ARM_LOW_POLE 1280
#define ARM_NEAR_HIGH_POLE 1600
#define ARM_HIGH_POLE 2205

PIDConstant arm_p = 0.05;
PIDConstant arm_i = 0;
PIDConstant arm_d = 0.5;
SensorVal arm_i_range = 100;
SensorVal arm_tolerance = 20;
MotorPower arm_min_power = 30;

PIDControl arm_control;

task arm_controller() {
    PIDControlConfig config;
    config.control = &arm_control;
    config.motor_power = &arm_power;
    config.current_value = &arm_pot_value;
    config.p_constant = &arm_p;
    config.i_constant = &arm_i;
    config.d_constant = &arm_d;
    config.i_range = &arm_i_range;
    config.tolerance = &arm_tolerance;
    config.min_power = &arm_min_power;
    run_control(&config);
}
