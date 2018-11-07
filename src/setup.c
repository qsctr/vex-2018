void pre_auton() {
    bDisplayCompetitionStatusOnLcd = false;
    startTask(lcd_updater);
}
