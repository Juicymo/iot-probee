// Private
boolean _motor_left_direction 	= MOTOR_DIRECTION_FORWARD; // true = forward, false = backward
boolean _motor_right_direction 	= MOTOR_DIRECTION_FORWARD; // true = forward, false = backward

void _hal_motor_off(byte motor) {
	if (motor == MOTOR_LEFT || motor == MOTOR_BOTH) {
		analogWrite(MOTOR_LEFT_PWM_PIN, 0);
		digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
		digitalWrite(MOTOR_LEFT_ENABLE_PIN, LOW);
	}
	if (motor == MOTOR_RIGHT || motor == MOTOR_BOTH) {
		analogWrite(MOTOR_RIGHT_PWM_PIN, 0);
		digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
		digitalWrite(MOTOR_RIGHT_ENABLE_PIN, LOW);
	}
}

void _hal_motor_drive_fwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT || motor == MOTOR_BOTH) {
		_motor_left_direction = MOTOR_DIRECTION_FORWARD;
		analogWrite(MOTOR_LEFT_PWM_PIN, pwm);
		digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
		digitalWrite(MOTOR_LEFT_ENABLE_PIN, HIGH);
	}
	if (motor == MOTOR_RIGHT || motor == MOTOR_BOTH) {
		_motor_right_direction = MOTOR_DIRECTION_FORWARD;
		analogWrite(MOTOR_RIGHT_PWM_PIN, pwm);
		digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
		digitalWrite(MOTOR_RIGHT_ENABLE_PIN, HIGH);
	}
}

void _hal_motor_drive_bwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT || motor == MOTOR_BOTH) {
		_motor_left_direction = MOTOR_DIRECTION_BACKWARD;
		analogWrite(MOTOR_LEFT_PWM_PIN, pwm);
		digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
		digitalWrite(MOTOR_LEFT_ENABLE_PIN, HIGH);
	}
	if (motor == MOTOR_RIGHT || motor == MOTOR_BOTH) {
		_motor_right_direction = MOTOR_DIRECTION_BACKWARD;
		analogWrite(MOTOR_RIGHT_PWM_PIN, pwm);
		digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
		digitalWrite(MOTOR_RIGHT_ENABLE_PIN, HIGH);
	}
}

void _hal_motor_brake(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT || motor == MOTOR_BOTH) {
		analogWrite(MOTOR_LEFT_PWM_PIN, pwm);

		if (_motor_left_direction == MOTOR_DIRECTION_FORWARD) {
			digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
		}
		else {
			digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
		}

		digitalWrite(MOTOR_LEFT_ENABLE_PIN, LOW);
	}
	if (motor == MOTOR_RIGHT || motor == MOTOR_BOTH) {
		analogWrite(MOTOR_RIGHT_PWM_PIN, pwm);

		if (_motor_right_direction == MOTOR_DIRECTION_FORWARD) {
			digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
		}
		else {
			digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
		}

		digitalWrite(MOTOR_RIGHT_ENABLE_PIN, LOW);
	}
}

// Public
void hal_motor_drive(byte motor, float speed) { // speed: fwd -> {0,5 - 1.0}, bwd -> {-0,5 - -1.0}
	TRACE("MOTOR ");
	TRACE(motor);
	TRACE(": ");
	TRACE(speed);

	byte pwm = abs(speed) * 255;

	TRACE(" -> ");
	TRACELN(pwm);

	if (pwm > 1) {
		if (speed > 0) {
			_hal_motor_drive_fwd(motor, pwm);
		}
		else {
			_hal_motor_drive_bwd(motor, pwm);
		}
	}
	else {
		_hal_motor_off(motor);
	}
}

void hal_motor_turn_left(float speed) {
	hal_motor_drive(MOTOR_LEFT, speed);
	hal_motor_drive(MOTOR_RIGHT, -speed);
}

void hal_motor_turn_right(float speed) {
	hal_motor_drive(MOTOR_LEFT, -speed);
	hal_motor_drive(MOTOR_RIGHT, speed);
}

void hal_motor_brake(byte motor) {
	float speed = MOTOR_SPEED_QUATER;
	byte pwm = abs(speed) * 255;
	_hal_motor_brake(motor, pwm);
}

void hal_motor_stop(byte motor) {
	_hal_motor_off(motor);
}

void setup_hal_motor() {
	pinMode(MOTOR_LEFT_DIRECTION_PIN, OUTPUT);
	pinMode(MOTOR_LEFT_ENABLE_PIN, OUTPUT);
	pinMode(MOTOR_RIGHT_DIRECTION_PIN, OUTPUT);
	pinMode(MOTOR_RIGHT_ENABLE_PIN, OUTPUT);
	pinMode(MOTOR_LEFT_PWM_PIN, OUTPUT);
	pinMode(MOTOR_RIGHT_PWM_PIN, OUTPUT);

	hal_motor_stop(MOTOR_BOTH);
}

void loop_hal_motor_test_drive() {
	TRACELN("Turn Right");
	hal_motor_drive(MOTOR_LEFT, MOTOR_SPEED_QUATER);
	delay(1000);
	hal_motor_drive(MOTOR_LEFT, MOTOR_SPEED_HALF);
	delay(1000);
	hal_motor_drive(MOTOR_LEFT, MOTOR_SPEED_FULL);
	delay(1000);

	hal_motor_stop(MOTOR_BOTH);
	delay(1000);

	TRACELN("Turn Left");
	hal_motor_drive(MOTOR_RIGHT, MOTOR_SPEED_QUATER);
	delay(1000);
	hal_motor_drive(MOTOR_RIGHT, MOTOR_SPEED_HALF);
	delay(1000);
	hal_motor_drive(MOTOR_RIGHT, MOTOR_SPEED_FULL);
	delay(1000);

	hal_motor_stop(MOTOR_BOTH);
	delay(1000);

	TRACELN("Move Forward");
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_QUATER);
	delay(1000);
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_HALF);
	delay(1000);
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_FULL);
	delay(1000);

	hal_motor_stop(MOTOR_BOTH);
	delay(1000);

	TRACELN("Move Backward");
	hal_motor_drive(MOTOR_BOTH, -MOTOR_SPEED_QUATER);
	delay(1000);
	hal_motor_drive(MOTOR_BOTH, -MOTOR_SPEED_HALF);
	delay(1000);
	hal_motor_drive(MOTOR_BOTH, -MOTOR_SPEED_FULL);
	delay(1000);

	hal_motor_stop(MOTOR_BOTH);
	delay(1000);
}
