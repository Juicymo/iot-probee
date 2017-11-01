// Private

// Public
void setup_hal_bluetooth() {
	// noop, because serial is already initialized in main setup method (in setup_debug())
}

void hal_bluetooth_loop() {
	if (Serial.available() > 0) {
		byte cmd = Serial.read();

		if (cmd == 'M') {
		  float speed_left = Serial.parseFloat();
		  float speed_right = Serial.parseFloat();

		  hal_motor_drive(M_L, speed_left);
		  hal_motor_drive(M_R, speed_right);
		}
		else {
		  hal_motor_stop(M_L);
		  hal_motor_stop(M_R);
		}

		cmd = 0;
	}
}
