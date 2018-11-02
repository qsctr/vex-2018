#if !(COLOR == "red" || COLOR == "blue")
#error "COLOR must be either \"red\" or \"blue\""
#endif

#if AUTO_MODE < 1 || AUTO_MODE > 3
#error "AUTO_MODE must be 1, 2, or 3"
#endif

#define LOOP_PERIOD 10
#define MOTOR_MAX 127
#define MOTOR_MIN -127
