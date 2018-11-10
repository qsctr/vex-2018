static void drive_red(SensorVal left, SensorVal right, Ms time = 0) {
    if (left < 0 && right < 0) {
        intake_power = 127;
    }
#ifdef AUTO_SKILLS
    if (left > 0 && right > 0) {
        intake_power = -127;
    }
#endif
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
    if (auto_mode == FrontShootDunkClimb || auto_mode == FrontShootDunkRam) {
        shoot();
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
#ifdef AUTO_SKILLS
        drive_red(-300, -300, 1000);
#else
        drive_red(-1000, -1000, 500);
#endif
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
#ifdef AUTO_SKILLS
            set_control(&arm_control, ARM_GROUND + 200);
            sync_control(&hand_control, HAND_FLAT + 100);
            drive_red(-400, 0, 1000);
            drive_red(400, 0, 1000);
            drive_red(0, -400, 1000);
            drive_red(0, 400, 1000);
            set_control(&arm_control, ARM_GROUND);
            sync_control(&hand_control, HAND_UP);
            drive_red(1000, 1000, 500);
            drive_red(300, 300, 300);
#else
            drive_red(1000, 1000, 300);
            drive_red(200, 200, 300);
#endif
            drive_red(0, 0, 500);
#ifdef AUTO_SKILLS
            drive_red(10000000, 10000000, 1800);
            drive_red(300, 300, 500);
            drive_red(0, 0, 500);
            drive_red(10000000, 10000000, 800);
#else
            drive_red(10000000, 10000000, 2000);
#endif
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
        if (color == Red) {
            drive(160, 90);
            sleep(1000);
            shoot();
            drive_red(300, 300);
        } else {

        }
        /*if (color == Red) {
            drive(500, 0);
        } else {
            drive_red(1000, 1000, 600);
            drive_red(0, 0, 500);
            drive_red(10000000, 10000000, 2000);
        }
        drive_red(1000, 1000);
        sleep(200);
        drive_red(1000, 1000);*/
    }
    disable_control(&base_left_control);
    base_left_power = 0;
    disable_control(&base_right_control);
    base_right_power = 0;
    while (1) sleep(LOOP_PERIOD);
}
// 179 91
