void pre_auton() {
    bDisplayCompetitionStatusOnLcd = false;
    setup_base();
    startTask(lcd_updater);
}
