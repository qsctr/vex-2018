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

void climb();

task autonomous() {
    start_all_tasks();
    if (auto_mode == FrontShootDunkClimb || auto_mode == FrontShootDunkRam) {
        shoot();
        set_control(&hand_control, HAND_FLAT);
        set_control(&arm_control, ARM_GROUND);
        if (color == Red) {
            drive(300, 0);
        } else {
            drive(0, 500);
        }
        drive_red(900, 900);
        set_control(&hand_control, HAND_LIFTED);
        if (color == Red) {
            drive(-230, 0);
            drive(-880, -880);
            drive(0, -540);
        } else {
            drive(0, -230);
            drive(-960, -960);
            drive(-550, 0);
        }
#ifdef AUTO_SKILLS
        drive_red(-300, -300, 1000);
#else
        if (color == Red) {
            drive(-1000, -1000, 400);
        } else {
            drive(-1000, -1000, 600);
        }
#endif
        drive_red(0, 0);
        dunk();
        wait_on_target(&hand_control);
        drive_red(-1000, -1000, 500);
        if (auto_mode == FrontShootDunkClimb) {
            drive_red(150, 150);
            set_control(&hand_control, HAND_UP);
            set_control(&arm_control, ARM_GROUND);
            drive_red(650, 0);
            drive_red(0, 750, 1500);
            climb();
        } else {
            sync_control(&arm_control, ARM_NEAR_HIGH_POLE);
            set_control(&arm_control, ARM_GROUND);
            set_control(&hand_control, HAND_UP);
            drive_red(0, 300);
            drive_red(-500, 500);
            drive_red(3000, 3000);
        }
    } else if (auto_mode == BackShootClimb) {
        // shoot();
        if (color == Red) {
            drive(1100, 470);
        } else {
            drive(570, 1310);
        }
        drive_red(400, 400, 2000);
        climb();
    } else if (auto_mode == BackShootOppositeMiddle) {
        sleep(13000);
        shoot();
    } else if (auto_mode == BackShootOppositeTop) {
        sleep(10000);
        drive_red(500, 500);
        shoot();
    } else if (auto_mode == BackShootCenterTop) {
        shoot();
        drive_red(680, 680);
        drive_red(450, 0, 2000);
        climb();
    }
    disable_control(&base_left_control);
    base_left_power = 0;
    disable_control(&base_right_control);
    base_right_power = 0;
    while (1) sleep(LOOP_PERIOD);
}

void climb() {
#ifdef AUTO_SKILLS
    sync_control(&arm_control, ARM_BALL_KNOCK);
    sync_control(&hand_control, HAND_BALL_KNOCK);
    drive_red(-400, 0, 1000);
    drive_red(400, 0, 1000);
    drive_red(0, -400, 1000);
    drive_red(0, 400, 1000);
    set_control(&arm_control, ARM_GROUND);
    set_control(&hand_control, HAND_UP);
    drive_red(1000, 1000, 500);
    drive_red(300, 300, 300);
#else
    drive_red(1000, 1000, 500);
    drive_red(200, 200, 300);
#endif
    drive_red(0, 0, 500);
#ifdef AUTO_SKILLS
    drive_red(10000000, 10000000, 1800);
    drive_red(300, 300, 500);
    drive_red(0, 0, 500);
    drive_red(10000000, 10000000, 1000);
#else
    drive_red(10000000, 10000000, 1800);
#endif
}
