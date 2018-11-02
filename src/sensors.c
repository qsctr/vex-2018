SensorVal base_left_encoder;
SensorVal base_right_encoder;
SensorVal arm_pot_value;
SensorVal hand_pot_value;

task sensor_updater() {
    while (1) {
        base_left_encoder = nMotorEncoder(base_left2);
        base_right_encoder = nMotorEncoder(base_right2);
        arm_pot_value = (SensorValue(arm_pot_left) + SensorValue(arm_pot_right)) / 2;
        hand_pot_value = SensorValue(hand_pot);
        sleep(LOOP_PERIOD);
    }
}
