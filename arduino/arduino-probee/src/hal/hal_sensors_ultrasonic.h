// Private
float hal_sensors_ultrasonic_perform_measure(byte pin_trigger, byte pin_echo) {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(pin_trigger, LOW);
  float duration = pulseIn(pin_echo, HIGH, 30 * 1000);

  // Calculate the distance (in cm) based on the speed of sound.
  float distance = duration / 58.2;

  return distance;
}

// Public
void setup_hal_sensors_ultrasonic() {
	// Turret
	pinMode(SONAR_TURRET_TRIGGER, OUTPUT);
	pinMode(SONAR_TURRET_ECHO, INPUT);
	// Forward
	pinMode(SONAR_FORWARD_TRIGGER, OUTPUT);
	pinMode(SONAR_FORWARD_ECHO, INPUT);
	// Backward
	pinMode(SONAR_BACKWARD_TRIGGER, OUTPUT);
	pinMode(SONAR_BACKWARD_ECHO, INPUT);
}

float hal_sensors_ultrasonic_turret_scan() {
	return hal_sensors_ultrasonic_perform_measure(SONAR_TURRET_TRIGGER, SONAR_TURRET_ECHO);
}

float hal_sensors_ultrasonic_forward_scan() {
	return hal_sensors_ultrasonic_perform_measure(SONAR_FORWARD_TRIGGER, SONAR_FORWARD_ECHO);
}

float hal_sensors_ultrasonic_backward_scan() {
	return hal_sensors_ultrasonic_perform_measure(SONAR_BACKWARD_TRIGGER, SONAR_BACKWARD_ECHO);
}
