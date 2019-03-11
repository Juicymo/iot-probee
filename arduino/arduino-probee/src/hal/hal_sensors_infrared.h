// Private
bool _hal_sensors_infrared_scan(pin) {
	return digitalRead(pin);
}

// Public
void setup_hal_sensors_infrared() {
	pinMode(INFRARED_FORWARD_LEFT, INPUT);
	pinMode(INFRARED_FORWARD_RIGHT, INPUT);
}

bool hal_sensors_infrared_forward_left_scan() {
	return _hal_sensors_infrared_scan(INFRARED_FORWARD_LEFT);
}

bool hal_sensors_infrared_forward_left_scan() {
	return _hal_sensors_infrared_scan(INFRARED_FORWARD_RIGHT);
}
