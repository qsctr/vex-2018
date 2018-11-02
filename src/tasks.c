void start_all_tasks() {
    startTask(motor_updater);
    startTask(sensor_updater);
    startTask(base_left_controller);
    startTask(base_right_controller);
    startTask(arm_controller);
    startTask(hand_controller);
}
