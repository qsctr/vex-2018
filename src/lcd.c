task lcd_updater() {
    // bLCDBacklight = true;
    displayLCDString(0, 0, "COLR XX COR=X.XX");
    displayLCDString(1, 0, "BAC=X.XX PE=X.XX");
    TControllerButtons prev = kButtonNone;
    while (1) {
        TControllerButtons cur = nLCDButtons;
        if (!bIfiAutonomousMode) {
            if ((cur & kButtonCenter) && !(prev & kButtonCenter)) {
                color = (Color) !color;
            }
            if ((cur & kButtonLeft) && !(prev & kButtonLeft)) {
                auto_mode--;
                if (auto_mode == 0) {
                    auto_mode = AutoModeEnd - 1;
                }
            } else if ((cur & kButtonRight) && !(prev & kButtonRight)) {
                auto_mode++;
                if (auto_mode == AutoModeEnd) {
                    auto_mode = (AutoMode) 1;
                }
            }
        }
        displayLCDString(0, 0, color == Red ? "RED " : "BLUE");
        displayLCDNumber(0, 5, auto_mode);
        displayLCDNumber(0, 12, nImmediateBatteryLevel * 0.001, 2);
        displayLCDNumber(1, 4, SensorValue(power_expander) / 280.0, 2);
        displayLCDNumber(1, 12, BackupBatteryLevel * 0.001, 2);
        prev = cur;
        sleep(LOOP_PERIOD);
    }
}
