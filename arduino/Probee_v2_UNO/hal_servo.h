
// Private
Servo servo;
int hal_servo_full_position = 0;
bool hal_servo_full_direction = SCAN_FULL_STARTING_DIRECTION; // true = right, false = left
int hal_servo_forward_position = 0;
bool hal_servo_forward_direction = SCAN_FORWARD_STARTING_DIRECTION; // true = right, false = left
int hal_servo_left_position = 0;
bool hal_servo_left_direction = SCAN_LEFT_STARTING_DIRECTION; // true = right, false = left
int hal_servo_right_position = 0;
bool hal_servo_right_direction = SCAN_RIGHT_STARTING_DIRECTION; // true = right, false = left

// Public - Rotation
void hal_servo_rotate_forward() {
	servo.write(ROTATION_FORWARD);
}

void hal_servo_rotate_left() {
	servo.write(ROTATION_LEFT);
}

void hal_servo_rotate_right() {
	servo.write(ROTATION_RIGHT);
}

void hal_servo_rotate(int position) {
	servo.write(position);
}

void setup_hal_servo() {
	servo.attach(SERVO_PIN);
	hal_servo_rotate_forward();
}

// Public - Scanning
void hal_servo_scan_full() {
	int val = (SONAR_MIN + hal_servo_full_position * SONAR_STEP);
	
	hal_servo_rotate(val);
	
	hal_servo_full_position += hal_servo_full_direction ? 1 : (-1);

	if (hal_servo_full_position >= SONAR_STEPS) {
	  hal_servo_full_direction = false;
	}
	else if (hal_servo_full_position <= 0) {
	  hal_servo_full_direction = true;
	}
}

void hal_servo_scan_full_reset() {
	hal_servo_full_position = ROTATION_FORWARD;
	hal_servo_rotate(hal_servo_full_position);
	hal_servo_full_direction = SCAN_FULL_STARTING_DIRECTION;
}

void hal_servo_scan_forward() {
	
}

void hal_servo_scan_forward_reset() {
	hal_servo_forward_position = ROTATION_FORWARD;
	hal_servo_rotate(hal_servo_forward_position);
	hal_servo_forward_direction = SCAN_FORWARD_STARTING_DIRECTION;
}

void hal_servo_scan_left() {
	
}

void hal_servo_scan_left_reset() {
	hal_servo_left_position = ROTATION_LEFT;
	hal_servo_rotate(hal_servo_left_position);
	hal_servo_left_direction = SCAN_LEFT_STARTING_DIRECTION;
}

void hal_servo_scan_right() {
	
}

void hal_servo_scan_right_reset() {
	hal_servo_right_position = ROTATION_RIGHT;
	hal_servo_rotate(hal_servo_right_position);
	hal_servo_right_direction = SCAN_RIGHT_STARTING_DIRECTION;
}