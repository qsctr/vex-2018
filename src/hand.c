#define HAND_RAM 100
#define HAND_FLAT 330
#define HAND_SLANT_FLIP 460
#define HAND_BALL_KNOCK 430
#define HAND_POLE_FLIP 1190
#define HAND_LIFTED 1340
#define HAND_UP 2000
#define HAND_FLIP 2100
#define HAND_DUNK 3170

PIDConstant hand_p = 0.3;
PIDConstant hand_i = 0.005;
PIDConstant hand_d = 0;
SensorVal hand_i_range = 100;
SensorVal hand_tolerance = 20;
MotorPower hand_min_power = 0;

PIDControl hand_control;
PIDControlConfig hand_control_config;

void init_hand() {
    hand_control_config.control = &hand_control;
    hand_control_config.motor_power = &hand_power;
    hand_control_config.current_value = &hand_pot_value;
    hand_control_config.p_constant = &hand_p;
    hand_control_config.i_constant = &hand_i;
    hand_control_config.d_constant = &hand_d;
    hand_control_config.i_range = &hand_i_range;
    hand_control_config.tolerance = &hand_tolerance;
    hand_control_config.min_power = &hand_min_power;
}

task hand_controller() {
    run_control(&hand_control_config);
}
