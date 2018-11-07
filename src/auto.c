static void drive_red(SensorVal left, SensorVal right, Ms time = 0) {
    if (left < 0 && right < 0) {
        intake_power = 127;
    }
    if (color == Red) {
        drive(left, right, time);
    } else {
        drive(right, left, time);
    }
    intake_power = 0;
}

int asdf;

task autonomous() {
    start_all_tasks();
    shoot();
    if (auto_mode == FrontShootDunkClimb || auto_mode == FrontShootDunkRam) {
        set_control(&hand_control, HAND_FLAT);
        set_control(&arm_control, ARM_GROUND);
        if (color == Red) {
            drive(270, 0);
            asdf = 1;
        } else {
            drive(0, 400);
        }
        drive_red(900, 900);
        set_control(&hand_control, HAND_LIFTED);
        drive_red(-200, 0);
        drive_red(-775, -775);
        drive_red(0, -540);
        drive_red(-1000, -1000, 500);
        drive_red(0, 0);
        dunk();
        wait_on_target(&hand_control);
        drive_red(-1000, -1000, 500);
        if (auto_mode == FrontShootDunkClimb) {
            drive_red(150, 150);
            set_control(&hand_control, HAND_UP);
            set_control(&arm_control, ARM_GROUND);
            drive_red(700, 0);
            drive_red(0, 700, 1500);
            drive_red(1000, 1000, 400);
            drive_red(0, 0, 500);
            drive_red(10000000, 10000000, 2000);
        } else {
            sync_control(&arm_control, ARM_NEAR_HIGH_POLE);
            set_control(&arm_control, ARM_GROUND);
            set_control(&hand_control, HAND_UP);
            drive_red(0, 300);
            drive_red(-500, 500);
            drive_red(3000, 3000);
        }
    } else {
        set_control(&arm_control, ARM_GROUND);
        set_control(&hand_control, HAND_FLAT);
        drive_red(1500, 1500);
        if (color == Red) {
            drive(1000, -1000);
        } else {
            drive(-1100, 1100);
        }
        drive_red(1000, 1000);
        sleep(200);
        drive_red(1000, 1000);
    }
    disable_control(&base_left_control);
    base_left_power = 0;
    disable_control(&base_right_control);
    base_right_power = 0;
    while (1) sleep(LOOP_PERIOD);
}
