bool dunker_running;

void dunk() {
    set_control(&arm_control, ARM_HIGH_POLE);
    while (arm_pot_value < ARM_GROUND + 300) {
        sleep(LOOP_PERIOD);
    }
    set_control(&hand_control, HAND_FLIP);
    sync_control(&arm_control, ARM_HIGH_POLE);
    set_control(&hand_control, HAND_DUNK);
}

task dunker() {
    dunk();
}

void init_dunker() {
    dunker_running = false;
}

void start_dunker() {
    if (dunker_running) return;
    startTask(dunker);
    dunker_running = true;
}

bool stop_dunker() {
    if (!dunker_running) return false;
    stopTask(dunker);
    dunker_running = false;
    return true;
}
