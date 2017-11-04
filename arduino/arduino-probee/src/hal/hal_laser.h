// Private
boolean _hal_laser_turret_on = false;

// Public
void hal_laser_on(byte laser) {
	if (laser == LASER_TURRET) {
		_hal_laser_turret_on = true;
		digitalWrite(LASER_TURRET_PIN, HIGH);
	}
}

void hal_laser_off(byte laser) {
	if (laser == LASER_TURRET) {
		_hal_laser_turret_on = false;
		digitalWrite(LASER_TURRET_PIN, LOW);
	}
}

boolean hal_laser_is_on(byte laser) {
	if (laser == LASER_TURRET) {
		return _hal_laser_turret_on;
	}
	else {
		return false;
	}
}

void setup_hal_laser() {
	pinMode(LASER_TURRET_PIN, OUTPUT);
	hal_laser_off(LASER_TURRET);
}
