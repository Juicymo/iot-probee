
// Motors
#define M_L 1
#define M_R 2

#define M_PWM_L 6
#define M_PWM_R 5
#define M_L1 9
#define M_L2 10
#define M_R1 7
#define M_R2 8

// Servos
#define SERVO_PIN 11
#define FORWARD_ROT 64

// Sonars
#define SONAR_ECHO 2
#define SONAR_TRIGR	A0

#define SONAR_ERR_BCK_ECHO 3
#define SONAR_ERR_BCK_TRIGR A1

#define SONAR_ERR_FWD_ECHO 4
#define SONAR_ERR_FWD_TRIGR A2

#define SONAR_STEPS 50
#define SONAR_MIN 20
#define SONAR_MAX 120
#define SONAR_STEP (256 - ((256 - SONAR_MAX) + SONAR_MIN)) / SONAR_STEPS

// Multitasking
#define SONAR_SPEED 50
#define SENSORS_SPEED 50
#define REASONING_SPEED 100
#define LCD_SPEED 500

#define SPEED_BLUETOOTH 100

// Movement
#define FWD_SAFE_DIST 15
#define BWD_SAFE_DIST 10

#define ROBOT_SPEED_FULL 1.0
#define ROBOT_SPEED_HALF 0.8
#define ROBOT_SPEED_QUATER 0.6

#define MOVE_FAST_FWD_SAFE_DIST 100
#define MOVE_NORM_FWD_SAFE_DIST 50
#define MOVE_SLOW_FWD_SAFE_DIST 30

// Rotation
#define LEFT_TURN_DIST_LIMIT 4
#define RIGHT_TURN_DIST_LIMIT 4

#define TURN_STEPS 1000
#define BACK_STEPS 200