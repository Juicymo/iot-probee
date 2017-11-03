// ----------------- PINS -----------------
// Motors
#define MOTOR_LEFT_PWM_PIN            7
#define MOTOR_LEFT_DIRECTION_PIN_1    6
#define MOTOR_LEFT_DIRECTION_PIN_2    9
#define MOTOR_RIGHT_PWM_PIN           8
#define MOTOR_RIGHT_DIRECTION_PIN_1   30
#define MOTOR_RIGHT_DIRECTION_PIN_2   31

// Lasers
#define LASER_TURRET_PIN          34

// LEDs
#define LED_REASONING_PIN         13

// Servos
#define SERVO_PIN                 12

// Sensors - Ultrasonic
#define SONAR_TURRET_ECHO_PIN       49
#define SONAR_TURRET_TRIGGER_PIN	  48

#define SONAR_FORWARD_ECHO_PIN      4
#define SONAR_FORWARD_TRIGGER_PIN   33

#define SONAR_BACKWARD_ECHO_PIN     5
#define SONAR_BACKWARD_TRIGGER_PIN  32

// LCD
#define LCD_I2C_ADDRESS             0x27

// ----------------- CONSTANTS -----------------
// Motors
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2
#define MOTOR_BOTH 3

// Lasers
#define LASER_TURRET 1
#define LASER_DISTANCE_ON 15

// LEDs
#define LED_REASONING 1

// Servos
#define ROTATION_FORWARD      64
#define ROTATION_LEFT         10
#define ROTATION_RIGHT        130
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
#define TICK_LCD 500
#define TICK_I2C 100

// Movement
#define MOTOR_SPEED_FULL    0.6 //1.0
#define MOTOR_SPEED_HALF    0.5 //0.8
#define MOTOR_SPEED_QUATER  0.4 //0.6

#define MOTOR_DIRECTION_FORWARD true
#define MOTOR_DIRECTION_BACKWARD false

// FSM Movement
// - Events
#define EVENT_FORWARD_OBSTACLE_NONE   	10
#define EVENT_FORWARD_OBSTACLE_FAR    	11
#define EVENT_FORWARD_OBSTACLE_NEAR   	12
#define EVENT_FORWARD_OBSTACLE_CLOSE    13
#define EVENT_FORWARD_OBSTACLE_BLOCKED  14

#define EVENT_BACKWARD_OBSTACLE_NONE   	20
#define EVENT_BACKWARD_OBSTACLE_FAR    	21
#define EVENT_BACKWARD_OBSTACLE_NEAR   	22
#define EVENT_BACKWARD_OBSTACLE_CLOSE   23
#define EVENT_BACKWARD_OBSTACLE_BLOCKED 24

#define EVENT_TURRET_OBSTACLE_NONE   		30
#define EVENT_TURRET_OBSTACLE_PRESENT   31

#define EVENT_REASONING_MOVE_FORWARD   	    40
#define EVENT_REASONING_MOVE_SLOW_FORWARD   41
#define EVENT_REASONING_TURN_RIGHT          42
#define EVENT_REASONING_TURN_LEFT           43
#define EVENT_REASONING_MOVE_BACKWARD       44
#define EVENT_REASONING_MOVE_SLOW_BACKWARD  45
#define EVENT_REASONING_STOPPED             46
// - States
DEFINE_STATE(idle);
DEFINE_STATE(reasoning);
DEFINE_STATE(brake);
DEFINE_STATE(stop);
DEFINE_STATE(forward);
DEFINE_STATE(slow_forward);
DEFINE_STATE(fast_forward);
DEFINE_STATE(backward);
DEFINE_STATE(slow_backward);
DEFINE_STATE(turn_left);
DEFINE_STATE(turn_right);

INIT_FSM(movement, idle);

// Collision Detection
#define COLLISION_NONE     10
#define COLLISION_FAR      11
#define COLLISION_NEAR     12
#define COLLISION_CLOSE    13
#define COLLISION_BLOCKED  14

#define DETECTION_DISTANCE_TURRET_FAR      100
#define DETECTION_DISTANCE_TURRET_NEAR     50
#define DETECTION_DISTANCE_TURRET_CLOSE    15
#define DETECTION_DISTANCE_TURRET_BLOCKED  5

#define DETECTION_DISTANCE_FORWARD_FAR     100
#define DETECTION_DISTANCE_FORWARD_NEAR    50
#define DETECTION_DISTANCE_FORWARD_CLOSE   20
#define DETECTION_DISTANCE_FORWARD_BLOCKED 5

#define DETECTION_DISTANCE_BACKWARD_FAR     100
#define DETECTION_DISTANCE_BACKWARD_NEAR    50
#define DETECTION_DISTANCE_BACKWARD_CLOSE   20
#define DETECTION_DISTANCE_BACKWARD_BLOCKED 5

// Rotation
#define LEFT_TURN_DIST_LIMIT 4
#define RIGHT_TURN_DIST_LIMIT 4

#define TURN_STEPS 1000
#define BACK_STEPS 200
