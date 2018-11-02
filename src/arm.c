#define ARM_GROUND 0
#define ARM_CLIMB 500
#define ARM_LOW_POLE 1000
#define ARM_NEAR_HIGH_POLE 1600
#define ARM_HIGH_POLE 1800
#define ARM_MAX 2000

static PConstant arm_p = 0.5;
static SensorVal arm_tolerance = 20;

PControl arm_control;

task arm_controller() {
    PControlConfig config;
    config.control = &arm_control;
    config.motor_power = &arm_power;
    config.current_value = &arm_pot_value;
    config.p_constant = arm_p;
    config.tolerance = arm_tolerance;
    run_control(&config);
}
