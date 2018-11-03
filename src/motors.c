MotorPower base_left_power;
MotorPower base_right_power;
MotorPower arm_power;
MotorPower hand_power;
MotorPower shooter_power;
MotorPower intake_power;

task motor_updater() {
    base_left_power = 0;
    base_right_power = 0;
    arm_power = 0;
    hand_power = 0;
    shooter_power = 0;
    intake_power = 0;
    while (1) {
        motor[base_left1] = motor[base_left2] = base_left_power;
        motor[base_right1] = motor[base_right2] = base_right_power;
        motor[arm_left] = motor[arm_right] = arm_power;
        motor[hand] = hand_power;
        motor[shooter_top] = motor[shooter_bottom] = shooter_power;
        motor[intake] = intake_power;
        sleep(LOOP_PERIOD);
    }
}
