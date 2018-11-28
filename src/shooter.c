#define SHOOTER_PERIOD 1000

void shoot() {
    shooter_power = 127;
    sleep(SHOOTER_PERIOD);
    shooter_power = 0;
}
