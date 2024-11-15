// Pin definitions

// LCD pins
#define LCD_RS 7
#define LCD_EN 6
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2
#define LCD_COLS 16
#define LCD_LINES 2

// Servo pins
#define SERVO_SIG 9
#define SERVO_MAX_DEG 180


// Game logic constants
#define MAX_ROUNDS 24
#define ROUND_RESTART_DELAY 3
#define MAX_POINTS_PER_ROUND 10
#define REACTION_CAP 2000

#define points(r_time) (((REACTION_CAP - r_time) * MAX_POINTS_PER_ROUND) / REACTION_CAP + 1)
#define servo_pos(r_no) ((r_no * SERVO_MAX_DEG) / MAX_ROUNDS)

// Game language constants
#define P1_NAME "P1"
#define P2_NAME "P2"
#define WINNER_MSG "wins!"
#define TIE_MSG "It's a tie!"
#define WELCOME_MSG "Quick Time"
#define IDLE_MSG "Press any key..."
#define STARTUP_MSG "Starting game..."