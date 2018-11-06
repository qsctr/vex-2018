#define ARM_GROUND 200
#define ARM_LOW_POLE 1280
#define ARM_NEAR_HIGH_POLE 1600
#define ARM_HIGH_POLE 2200

PIDConstant arm_p = 0.09;
PIDConstant arm_i = 0;
PIDConstant arm_d = 0;
SensorVal arm_i_range = 100;
SensorVal arm_tolerance = 20;
MotorPower arm_min_power = 30;

PIDControl arm_control;

task arm_controller() {
    PIDControlConfig config;
    config.control = &arm_control;
    config.motor_power = &arm_power;
    config.current_value = &arm_pot_value;
    PIDSetting *settings[1];
    PIDSetting setting;
    settings[0] = &setting;
    setting.p_constant = &arm_p;
    setting.i_constant = &arm_i;
    setting.d_constant = &arm_d;
    setting.i_range = &arm_i_range;
    config.pid_settings = (PIDSetting **) settings;
    config.tolerance = &arm_tolerance;
    config.min_power = &arm_min_power;
    run_control(&config);
}
