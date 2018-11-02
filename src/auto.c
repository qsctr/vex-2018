void pre_auton() {
    reset_base_encoders();
}

static void drive_red(SensorVal left, SensorVal right) {
#if COLOR == "red"
    drive(left, right);
#elif COLOR == "blue"
    drive(right, left);
#endif
}

task autonomous() {
    start_all_tasks();
    shoot();
#if AUTO_MODE == 1 || AUTO_MODE == 2
#if COLOR == "red"
    drive(600, -600);
#elif COLOR == "blue"
    drive(-700, 700);
#endif
    drive_red(2000, 2000);
    sync_control(&hand_control, HAND_LIFTED);
    drive_red(-100, 100);
    drive_red(-2500, -3000);
    dunk();
    wait_on_target(&hand_control);
#if AUTO_MODE == 1
    drive_red(200, 200);
    set_control(&hand_control, HAND_FLAT);
    set_control(&arm_control, ARM_CLIMB);
    drive_red(1000, 0);
    drive_red(0, 1000);
    drive_red(500, 500);
    sleep(200);
    drive_red(1000, 1000);
#elif AUTO_MODE == 2
    sync_control(&arm_control, ARM_NEAR_HIGH_POLE);
    set_control(&arm_control, ARM_GROUND);
    set_control(&hand_control, HAND_UP);
    drive_red(0, 300);
    drive_red(-500, 500);
    drive_red(3000, 3000);
#endif
#elif AUTO_MODE == 3
    set_control(&arm_control, ARM_CLIMB);
    set_control(&hand_control, HAND_FLAT);
    drive_red(1500, 1500);
#if COLOR == "red"
    drive(1000, -1000);
#elif COLOR == "blue"
    drive(-1100, 1100);
#endif
    drive_red(1000, 1000);
    sleep(200);
    drive_red(1000, 1000);
#endif
}
