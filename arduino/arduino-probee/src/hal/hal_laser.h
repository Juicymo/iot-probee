// Private

// Public
void hal_laser_on(byte laser) {
	if (laser == LASER_TURRET) {
		digitalWrite(LASER_TURRET_PIN, HIGH);
	}
}

void hal_laser_off(byte laser) {
	if (laser == LASER_TURRET) {
		digitalWrite(LASER_TURRET_PIN, LOW);
	}
}

void setup_hal_laser() {
	pinMode(LASER_TURRET_PIN, OUTPUT);
	hal_laser_off(LASER_TURRET);
}
