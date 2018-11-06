#define HAND_FLAT 400
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
    PIDSetting *settings[1];
    PIDSetting setting;
    settings[0] = &setting;
    setting.p_constant = &hand_p;
    setting.i_constant = &hand_i;
    setting.d_constant = &hand_d;
    setting.i_range = &hand_i_range;
    config.pid_settings = (PIDSetting **) settings;
    config.tolerance = &hand_tolerance;
    config.min_power = &hand_min_power;
    run_control(&config);
}
