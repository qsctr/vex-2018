#define JOYSTICK_DEADBAND 20

#define joysticks_active(c3, c2) (abs(vexRT[c3]) > JOYSTICK_DEADBAND || abs(vexRT[c2]) > JOYSTICK_DEADBAND)

static void disable_arm_preset() {
    disable_control(&arm_control);
    if (stop_dunker()) {
        disable_control(&hand_control);
    }
}

static void disable_hand_preset() {
    disable_control(&hand_control);
    if (stop_dunker()) {
        disable_control(&arm_control);
    }
}

task usercontrol() {
    start_all_tasks();
    init_dunker();
    while (1) {

        // base
        if (joysticks_active(Ch3Xmtr2, Ch2Xmtr2) && !joysticks_active(Ch3, Ch2)) {
            base_left_power = vexRT[Ch3Xmtr2];
            base_right_power = vexRT[Ch2Xmtr2];
        } else {
            base_left_power = vexRT[Ch3];
            base_right_power = vexRT[Ch2];
        }

        // arm
        if (vexRT[Btn6U]) {
            disable_arm_preset();
            arm_power = 50;
        } else if (vexRT[Btn6D]) {
            disable_arm_preset();
            arm_power = -50;
            // TODO: move hand if unsafe
        } else if (!arm_control.enabled) {
            arm_power = 0;
        }

        // hand
        if (vexRT[Btn5U]) {
            disable_hand_preset();
            hand_power = 127;
        } else if (vexRT[Btn5D]) {
            disable_hand_preset();
            hand_power = -127;
        } else if (!hand_control.enabled) {
            hand_power = 0;
        }

        // presets
        if (vexRT[Btn8R]) {
            start_dunker();
        } else if (vexRT[Btn8D]) {
            stop_dunker();
            set_control(&arm_control, ARM_LOW_POLE);
            set_control(&hand_control, HAND_LIFTED);
        } else if (vexRT[Btn7L]) {
            stop_dunker();
            set_control(&arm_control, ARM_POLE_FLIP);
            set_control(&hand_control, HAND_POLE_FLIP);
        } else if (vexRT[Btn7U]) {
            stop_dunker();
            set_control(&arm_control, ARM_POLE_FLIP_UP);
        } else if (vexRT[Btn7D]) {
            stop_dunker();
            set_control(&arm_control, ARM_GROUND);
            set_control(&hand_control, HAND_FLAT);
        } else if (vexRT[Btn8L]) {
            stop_dunker();
            set_control(&arm_control, ARM_RAM);
            set_control(&hand_control, HAND_RAM);
        }

        // shooter
        shooter_power = vexRT[Btn5UXmtr2] * 127;

        // intake
        if (vexRT[Btn6UXmtr2]) {
            intake_power = 127;
        } else if (vexRT[Btn6DXmtr2]) {
            intake_power = -127;
        } else if (vexRT[Btn8UXmtr2]) {
            intake_power = 70;
        } else if (vexRT[Btn8DXmtr2]) {
            intake_power = -70;
        } else {
            intake_power = 0;
        }

        if (abs(vexRT[AccelX]) > 10) {
            playImmediateTone(1000 + vexRT[AccelX] * 5, LOOP_PERIOD);
        }

        sleep(LOOP_PERIOD);

    }
}
