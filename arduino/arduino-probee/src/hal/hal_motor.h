// Private
void hal_motor_off(byte motor) {
	if (motor == MOTOR_LEFT) {
		analogWrite(M_PWM_L, 0);
		digitalWrite(M_L1, LOW);
		digitalWrite(M_L2, LOW);
	}
	else {
		analogWrite(M_PWM_R, 0);
		digitalWrite(M_R1, LOW);
		digitalWrite(M_R2, LOW);
	}
}

void hal_motor_drive_fwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT) {
		analogWrite(M_PWM_L, pwm);
		digitalWrite(M_L1, LOW);
		digitalWrite(M_L2, HIGH);
	}
	else {
		analogWrite(M_PWM_R, pwm);
		digitalWrite(M_R1, LOW);
		digitalWrite(M_R2, HIGH);
	}
}

void hal_motor_drive_bwd(byte motor, byte pwm) {
	if (motor == MOTOR_LEFT) {
		analogWrite(M_PWM_L, pwm);
		digitalWrite(M_L1, HIGH);
		digitalWrite(M_L2, LOW);
	}
	else {
		analogWrite(M_PWM_R, pwm);
		digitalWrite(M_R1, HIGH);
		digitalWrite(M_R2, LOW);
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
			hal_motor_drive_fwd(motor, pwm);
		}
		else {
			hal_motor_drive_bwd(motor, pwm);
		}
	}
	else {
		hal_motor_off(motor);
	}
}

void hal_motor_stop(byte motor) {
	hal_motor_off(motor);
}

void setup_hal_motor() {
	pinMode(M_L1, OUTPUT);
	pinMode(M_L2, OUTPUT);
	pinMode(M_R1, OUTPUT);
	pinMode(M_R2, OUTPUT);
	pinMode(M_PWM_L, OUTPUT);
	pinMode(M_PWM_R, OUTPUT);

	hal_motor_stop(MOTOR_LEFT);
	hal_motor_stop(MOTOR_RIGHT);
}
