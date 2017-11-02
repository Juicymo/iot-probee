// ----------------- PINS -----------------
// Motors
#define MOTOR_LEFT_ENABLE_PIN     30
#define MOTOR_LEFT_PWM_PIN        7
#define MOTOR_LEFT_DIRECTION_PIN  6
#define MOTOR_RIGHT_ENABLE_PIN    31
#define MOTOR_RIGHT_PWM_PIN       8
#define MOTOR_RIGHT_DIRECTION_PIN 9

// Lasers
#define LASER_TURRET_PIN      34

// Servos
#define SERVO_PIN             12

// Sensors - Ultrasonic
#define SONAR_TURRET_ECHO_PIN       49
#define SONAR_TURRET_TRIGGER_PIN	  48

#define SONAR_FORWARD_ECHO_PIN      4
#define SONAR_FORWARD_TRIGGER_PIN   33

#define SONAR_BACKWARD_ECHO_PIN     5
#define SONAR_BACKWARD_TRIGGER_PIN  32

// ----------------- CONSTANTS -----------------
// Motors
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2
#define MOTOR_BOTH 3

// Lasers
#define LASER_TURRET 1
#define LASER_DISTANCE_ON 15

// Servos
#define ROTATION_FORWARD      64
#define ROTATION_LEFT         20
#define ROTATION_RIGHT        120
// true = left, false = right
#define SCAN_FULL_STARTING_DIRECTION true
#define SCAN_FORWARD_STARTING_DIRECTION true
#define SCAN_LEFT_STARTING_DIRECTION true
#define SCAN_RIGHT_STARTING_DIRECTION true

#define SCANNING_ALL          0
#define SCANNING_FULL         1
#define SCANNING_FORWARD      2
#define SCANNING_LEFT         3
#define SCANNING_RIGHT        4

// Sensors - Ultrasonic
#define SONAR_NUM            3 // Number of sensors.
#define SONAR_MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define SONAR_PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

#define SONAR_SENSOR_TURRET     0
#define SONAR_SENSOR_FORWARD    1
#define SONAR_SENSOR_BACKWARD   2

// Sensors - Infrared
//#define INFRARED_FORWARD_LEFT 10
//#define INFRARED_FORWARD_RIGHT 11
// TBD

// Sensors - Turret Scanner
#define SONAR_STEPS 50
#define SONAR_MIN 20
#define SONAR_MAX 120
#define SONAR_STEP (256 - ((256 - SONAR_MAX) + SONAR_MIN)) / SONAR_STEPS

// Communication i2c
#define I2C_ADDRESS 0x04

// Multitasking
#define SONAR_SPEED 50
#define SENSORS_SPEED 50
#define REASONING_SPEED 100
#define LCD_SPEED 500

#define TICK_SCANNING 50
#define TICK_BLUETOOTH 100
#define TICK_AI 100
#define TICK_I2C 100

// Movement
#define MOTOR_SPEED_FULL 1.0
#define MOTOR_SPEED_HALF 0.8
#define MOTOR_SPEED_QUATER 0.6

// Collision Detection
#define DETECTION_DISTANCE_TURRET_FAR      100
#define DETECTION_DISTANCE_TURRET_NEAR     50
#define DETECTION_DISTANCE_TURRET_CLOSE    20
#define DETECTION_DISTANCE_TURRET_BLOCKED  5

#define DETECTION_DISTANCE_FORWARD_FAR     100
#define DETECTION_DISTANCE_FORWARD_NEAR    50
#define DETECTION_DISTANCE_FORWARD_CLOSE   20
#define DETECTION_DISTANCE_FORWARD_BLOCKED 5

#define DETECTION_DISTANCE_BACKEND_FAR     100
#define DETECTION_DISTANCE_BACKEND_NEAR    50
#define DETECTION_DISTANCE_BACKEND_CLOSE   20
#define DETECTION_DISTANCE_BACKEND_BLOCKED 5

// Rotation
#define LEFT_TURN_DIST_LIMIT 4
#define RIGHT_TURN_DIST_LIMIT 4

#define TURN_STEPS 1000
#define BACK_STEPS 200
