// Private
Servo _servo;
int _hal_servo_full_position = 0;
bool _hal_servo_full_direction = SCAN_FULL_STARTING_DIRECTION; // true = right, false = left
int _hal_servo_forward_position = 0;
bool _hal_servo_forward_direction = SCAN_FORWARD_STARTING_DIRECTION; // true = right, false = left
int _hal_servo_left_position = 0;
bool _hal_servo_left_direction = SCAN_LEFT_STARTING_DIRECTION; // true = right, false = left
int _hal_servo_right_position = 0;
bool _hal_servo_right_direction = SCAN_RIGHT_STARTING_DIRECTION; // true = right, false = left

bool _hal_servo_is_scanning_full = false;

void _hal_servo_rotate(int position) {
	_servo.write(position);
}

void _hal_servo_scan_full_step() {
	int val = (SONAR_MIN + _hal_servo_full_position * SONAR_STEP);

	_hal_servo_rotate(val);

	_hal_servo_full_position += _hal_servo_full_direction ? 1 : (-1);

	if (_hal_servo_full_position >= SONAR_STEPS) {
	  _hal_servo_full_direction = false;
	}
	else if (_hal_servo_full_position <= 0) {
	  _hal_servo_full_direction = true;
	}
}

void _hal_servo_scan_full_reset() {
	_hal_servo_full_position = ROTATION_FORWARD;
	_hal_servo_rotate(_hal_servo_full_position);
	_hal_servo_full_direction = SCAN_FULL_STARTING_DIRECTION;
}

void _hal_servo_scan_forward() {

}

void _hal_servo_scan_forward_reset() {
	_hal_servo_forward_position = ROTATION_FORWARD;
	_hal_servo_rotate(_hal_servo_forward_position);
	_hal_servo_forward_direction = SCAN_FORWARD_STARTING_DIRECTION;
}

void _hal_servo_scan_left() {

}

void _hal_servo_scan_left_reset() {
	_hal_servo_left_position = ROTATION_LEFT;
	_hal_servo_rotate(_hal_servo_left_position);
	_hal_servo_left_direction = SCAN_LEFT_STARTING_DIRECTION;
}

void _hal_servo_scan_right() {

}

void _hal_servo_scan_right_reset() {
	_hal_servo_right_position = ROTATION_RIGHT;
	_hal_servo_rotate(_hal_servo_right_position);
	_hal_servo_right_direction = SCAN_RIGHT_STARTING_DIRECTION;
}

// Public - Scanning
void hal_servo_start_scanning(byte scanning) {
	if (scanning == SCANNING_FULL) {
		_hal_servo_is_scanning_full = true;
	}
}

void hal_servo_stop_scanning(byte scanning) {
	if (scanning == SCANNING_FULL || scanning == SCANNING_ALL) {
		_hal_servo_is_scanning_full = false;
	}
}

// Public - Rotation
void hal_servo_rotate_forward() {
	_hal_servo_rotate(ROTATION_FORWARD);
}

void hal_servo_rotate_left() {
	_hal_servo_rotate(ROTATION_LEFT);
}

void hal_servo_rotate_right() {
	_hal_servo_rotate(ROTATION_RIGHT);
}

void hal_servo_rotate(int position) {
	_hal_servo_rotate(position);
}

// Public - Setup & Loop
void setup_hal_servo() {
	_servo.attach(SERVO_PIN);
	hal_servo_rotate_forward();
	hal_servo_stop_scanning(SCANNING_ALL);
}

void hal_servo_loop() {
	if (_hal_servo_is_scanning_full) {
		_hal_servo_scan_full_step();
	}
}
