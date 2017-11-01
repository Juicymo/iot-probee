// Variables
unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {              // Sensor object array.
  NewPing(SONAR_TURRET_TRIGGER_PIN, SONAR_TURRET_ECHO_PIN, SONAR_MAX_DISTANCE),    // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(SONAR_FORWARD_TRIGGER_PIN, SONAR_FORWARD_ECHO_PIN, SONAR_MAX_DISTANCE),
  NewPing(SONAR_BACKWARD_TRIGGER_PIN, SONAR_BACKWARD_ECHO_PIN, SONAR_MAX_DISTANCE)
};

// Private
void _echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void _oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");

    if (i == SONAR_SENSOR_TURRET) {
      if (cm[i] <= LASER_DISTANCE_ON) {
        hal_laser_on(LASER_TURRET);
      } else {
        hal_laser_off(LASER_TURRET);
      }
    }
  }
  Serial.println();
}

// Public
void setup_hal_sensors_ultrasonic() {
	pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + SONAR_PING_INTERVAL;
}

void loop_hal_sensors_ultrasonic() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += SONAR_PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) _oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(_echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
}
