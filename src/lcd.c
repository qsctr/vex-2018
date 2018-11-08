task lcd_updater() {
    bLCDBacklight = true;
    displayLCDString(0, 0, "COLR X  COR=XXXX");
    displayLCDString(1, 0, "BAC=XXXX PE=XXXX");
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
        displayLCDNumber(0, 12, nImmediateBatteryLevel);
        displayLCDNumber(1, 4, BackupBatteryLevel);
        displayLCDNumber(1, 12, SensorValue(power_expander) / (45.6 * 4) * 1000);
        prev = cur;
        sleep(LOOP_PERIOD);
    }
}
