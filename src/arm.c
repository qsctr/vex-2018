#define ARM_GROUND 200
#define ARM_BALL_KNOCK 400
#define ARM_SLANT_FLIP 530
#define ARM_POLE_FLIP 850
#define ARM_RAM 870
#define ARM_LOW_POLE 1330
#define ARM_POLE_FLIP_UP 1540
#define ARM_NEAR_HIGH_POLE 1600
#define ARM_HIGH_POLE 2230

PIDConstant arm_p = 0.15;
PIDConstant arm_i = 0;
PIDConstant arm_d = 1.2;
SensorVal arm_i_range = 100;
SensorVal arm_tolerance = 20;
MotorPower arm_min_power = 30;

PIDControl arm_control;
PIDControlConfig arm_control_config;

void init_arm() {
    arm_control_config.control = &arm_control;
    arm_control_config.motor_power = &arm_power;
    arm_control_config.current_value = &arm_pot_value;
    arm_control_config.p_constant = &arm_p;
    arm_control_config.i_constant = &arm_i;
    arm_control_config.d_constant = &arm_d;
    arm_control_config.i_range = &arm_i_range;
    arm_control_config.tolerance = &arm_tolerance;
    arm_control_config.min_power = &arm_min_power;
}

task arm_controller() {
    run_control(&arm_control_config);
}
