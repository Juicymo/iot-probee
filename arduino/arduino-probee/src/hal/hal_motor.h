// Private
void _hal_motor_off(byte motor) {
	if (motor == MOTOR_LEFT) {
		analogWrite(MOTOR_LEFT_PWM, 0);
		digitalWrite(MOTOR_LEFT_DIRECTION, LOW);
		digitalWrite(MOTOR_LEFT_ENABLE, LOW);
	}
	else {
		analogWrite(MOTOR_RIGHT_PWM, 0);
		digitalWrite(MOTOR_RIGHT_DIRECTION, LOW);
		digitalWrite(MOTOR_RIGHT_ENABLE, LOW);
	}
}

void _hal_motor_drive_fwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT) {
		analogWrite(MOTOR_LEFT_PWM, pwm);
		digitalWrite(MOTOR_LEFT_DIRECTION, LOW);
		digitalWrite(MOTOR_LEFT_ENABLE, HIGH);
	}
	else {
		analogWrite(MOTOR_RIGHT_PWM, pwm);
		digitalWrite(MOTOR_RIGHT_DIRECTION, LOW);
		digitalWrite(MOTOR_RIGHT_ENABLE, HIGH);
	}
}

void _hal_motor_drive_bwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT) {
		analogWrite(MOTOR_LEFT_PWM, pwm);
		digitalWrite(MOTOR_LEFT_DIRECTION, HIGH);
		digitalWrite(MOTOR_LEFT_ENABLE, LOW);
	}
	else {
		analogWrite(MOTOR_RIGHT_PWM, pwm);
		digitalWrite(MOTOR_RIGHT_DIRECTION, HIGH);
		digitalWrite(MOTOR_RIGHT_ENABLE, LOW);
	}
}

// Public
void hal_motor_drive(byte motor, float speed) { // speed: fwd -> {0,5 - 1.0}, bwd -> {-0,5 - -1.0}
	TRACE("V motor ");
	TRACE(motor);
	TRACE(": ");
	TRACELN(speed);

	byte pwm = abs(speed) * 255;

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

void hal_motor_stop(byte motor) {
	_hal_motor_off(motor);
}

void setup_hal_motor() {
	pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
	pinMode(MOTOR_LEFT_ENABLE, OUTPUT);
	pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
	pinMode(MOTOR_RIGHT_ENABLE, OUTPUT);
	pinMode(MOTOR_LEFT_PWM, OUTPUT);
	pinMode(MOTOR_RIGHT_PWM, OUTPUT);

	hal_motor_stop(MOTOR_LEFT);
	hal_motor_stop(MOTOR_RIGHT);
}
