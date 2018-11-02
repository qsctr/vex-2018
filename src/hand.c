#define HAND_FLAT 400
#define HAND_LIFTED 800
#define HAND_UP 1200
#define HAND_FLIP 1500
#define HAND_DUNK 2000

static PConstant hand_p = 0.5;
static SensorVal hand_tolerance = 20;

PControl hand_control;

task hand_controller() {
    PControlConfig config;
    config.control = &hand_control;
    config.motor_power = &hand_power;
    config.current_value = &hand_pot_value;
    config.p_constant = hand_p;
    config.tolerance = hand_tolerance;
    run_control(&config);
}
