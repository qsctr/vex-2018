#define HAND_FLAT 330
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

task hand_controller() {
    PIDControlConfig config;
    config.control = &hand_control;
    config.motor_power = &hand_power;
    config.current_value = &hand_pot_value;
    config.p_constant = &hand_p;
    config.i_constant = &hand_i;
    config.d_constant = &hand_d;
    config.i_range = &hand_i_range;
    config.tolerance = &hand_tolerance;
    config.min_power = &hand_min_power;
    run_control(&config);
}
