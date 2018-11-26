void pre_auton() {
    bDisplayCompetitionStatusOnLcd = false;
    init_base();
    init_arm();
    init_hand();
    startTask(lcd_updater);
}
