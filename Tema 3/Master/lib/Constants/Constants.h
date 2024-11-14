// Pin definitions

// LCD pins
#define LCD_RS 7
#define LCD_EN 6
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

// Servo pins
#define SERVO_SIG 9


// Game logic constants
#define MAX_ROUNDS 24
#define ROUND_RESTART_DELAY 3
#define MAX_POINTS_PER_ROUND 10
#define REACTION_CAP 1000

#define points(r_time) (((1000 - r_time) * MAX_POINTS_PER_ROUND) / REACTION_CAP + 1)
