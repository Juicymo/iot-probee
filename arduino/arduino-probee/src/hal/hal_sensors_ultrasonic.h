// Variables
// Private
unsigned long _pingTimers[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
uint8_t _currentSensor = 0;           // Keeps track of which sensor is active.
NewPing _sonars[SONAR_NUM] = {        // Sensor object array.
  NewPing(SONAR_TURRET_TRIGGER_PIN, SONAR_TURRET_ECHO_PIN, SONAR_MAX_DISTANCE),    // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(SONAR_FORWARD_TRIGGER_PIN, SONAR_FORWARD_ECHO_PIN, SONAR_MAX_DISTANCE),
  NewPing(SONAR_BACKWARD_TRIGGER_PIN, SONAR_BACKWARD_ECHO_PIN, SONAR_MAX_DISTANCE)
};

// Public (Readonly!)
byte hal_sensors_ultrasonic_collisions[SONAR_NUM];
unsigned int hal_sensors_ultrasonic_distances_cm[SONAR_NUM];         // Where the ping distances are stored.

// Functions
// Private
void _sensors_ultrasonic_echo_check() { // If ping received, set the sensor distance to array.
  if (_sonars[_currentSensor].check_timer())
    hal_sensors_ultrasonic_distances_cm[_currentSensor] = _sonars[_currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void _hal_sensors_ultrasonic_handle_laser(uint8_t i) {
  if (i == SONAR_SENSOR_TURRET) {
    if (hal_servo_is_scanning(SCANNING_FULL) || hal_laser_is_on(LASER_TURRET)) {
      if (hal_sensors_ultrasonic_distances_cm[i] <= LASER_DISTANCE_ON) {
        hal_laser_on(LASER_TURRET);
        hal_servo_stop_scanning(SCANNING_FULL);
      } else {
        hal_laser_off(LASER_TURRET);
        hal_servo_start_scanning(SCANNING_FULL);
      }
    }
  }
}

void _hal_sensors_ultrasonic_update_distance_for_sensor(uint8_t i, byte far, byte near, byte close, byte blocked) {
  unsigned int distance = hal_sensors_ultrasonic_distances_cm[i];

  if (distance > far) {
    hal_sensors_ultrasonic_collisions[i] = COLLISION_NONE;
  }
  else if (distance <= far && distance > near) {
    hal_sensors_ultrasonic_collisions[i] = COLLISION_FAR;
  }
  else if (distance <= near && distance > close) {
    hal_sensors_ultrasonic_collisions[i] = COLLISION_NEAR;
  }
  else if (distance <= close && distance > blocked) {
    hal_sensors_ultrasonic_collisions[i] = COLLISION_CLOSE;
  }
  else { // distance <= blocked
    hal_sensors_ultrasonic_collisions[i] = COLLISION_BLOCKED;
  }
}

void _hal_sensors_ultrasonic_handle_distances_update(uint8_t i) {
  if (i == SONAR_SENSOR_TURRET) {
    _hal_sensors_ultrasonic_update_distance_for_sensor(i,
       DETECTION_DISTANCE_TURRET_FAR,
       DETECTION_DISTANCE_TURRET_NEAR,
       DETECTION_DISTANCE_TURRET_CLOSE,
       DETECTION_DISTANCE_TURRET_BLOCKED
    );
  }
  else if (i == SONAR_SENSOR_FORWARD) {
    _hal_sensors_ultrasonic_update_distance_for_sensor(i,
       DETECTION_DISTANCE_FORWARD_FAR,
       DETECTION_DISTANCE_FORWARD_NEAR,
       DETECTION_DISTANCE_FORWARD_CLOSE,
       DETECTION_DISTANCE_FORWARD_BLOCKED
    );
  }
  else if (i == SONAR_SENSOR_BACKWARD) {
    _hal_sensors_ultrasonic_update_distance_for_sensor(i,
       DETECTION_DISTANCE_BACKWARD_FAR,
       DETECTION_DISTANCE_BACKWARD_NEAR,
       DETECTION_DISTANCE_BACKWARD_CLOSE,
       DETECTION_DISTANCE_BACKWARD_BLOCKED
    );
  }
  else {
    WARNING("Cannot update distance for unknown ultrasonic sensor!")
  }
}

void _hal_sensors_ultrasonic_update_fsm_events_for_sensor_turret(uint8_t i) {
  byte collision = hal_sensors_ultrasonic_collisions[i];

  if (collision >= COLLISION_CLOSE) {
    fsm_movement.trigger(EVENT_TURRET_OBSTACLE_PRESENT);
  }
  else {
    fsm_movement.trigger(EVENT_TURRET_OBSTACLE_NONE);
  }
}

void _hal_sensors_ultrasonic_update_fsm_events_for_sensor_forward(uint8_t i) {
  byte collision = hal_sensors_ultrasonic_collisions[i];

  if (collision == COLLISION_NONE) {
    fsm_movement.trigger(EVENT_FORWARD_OBSTACLE_NONE);
  }
  else if (collision == COLLISION_FAR) {
    fsm_movement.trigger(EVENT_FORWARD_OBSTACLE_FAR);
  }
  else if (collision == COLLISION_NEAR) {
    fsm_movement.trigger(EVENT_FORWARD_OBSTACLE_NEAR);
  }
  else if (collision == COLLISION_CLOSE) {
    fsm_movement.trigger(EVENT_FORWARD_OBSTACLE_CLOSE);
  }
  else { // collision == COLLISION_BLOCKED
    fsm_movement.trigger(EVENT_FORWARD_OBSTACLE_BLOCKED);
  }
}

void _hal_sensors_ultrasonic_update_fsm_events_for_sensor_backward(uint8_t i) {
  byte collision = hal_sensors_ultrasonic_collisions[i];

  if (collision == COLLISION_NONE) {
    fsm_movement.trigger(EVENT_BACKWARD_OBSTACLE_NONE);
  }
  else if (collision == COLLISION_FAR) {
    fsm_movement.trigger(EVENT_BACKWARD_OBSTACLE_FAR);
  }
  else if (collision == COLLISION_NEAR) {
    fsm_movement.trigger(EVENT_BACKWARD_OBSTACLE_NEAR);
  }
  else if (collision == COLLISION_CLOSE) {
    fsm_movement.trigger(EVENT_BACKWARD_OBSTACLE_CLOSE);
  }
  else { // collision == COLLISION_BLOCKED
    fsm_movement.trigger(EVENT_BACKWARD_OBSTACLE_BLOCKED);
  }
}

void _hal_sensors_ultrasonic_handle_fsm_events_update(uint8_t i) {
  if (i == SONAR_SENSOR_TURRET) {
    _hal_sensors_ultrasonic_update_fsm_events_for_sensor_turret(i);
  }
  else if (i == SONAR_SENSOR_FORWARD) {
    _hal_sensors_ultrasonic_update_fsm_events_for_sensor_forward(i);
  }
  else if (i == SONAR_SENSOR_BACKWARD) {
    _hal_sensors_ultrasonic_update_fsm_events_for_sensor_backward(i);
  }
  else {
    WARNING("Cannot update FSM events for unknown ultrasonic sensor!")
  }
}

void _sensors_ultrasonic_one_sensor_cycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    // Serial.print(i);
    // Serial.print("=");
    // Serial.print(hal_sensors_ultrasonic_distances_cm[i]);
    // Serial.print("cm ");

    _hal_sensors_ultrasonic_handle_distances_update(i);
    _hal_sensors_ultrasonic_handle_fsm_events_update(i);
    _hal_sensors_ultrasonic_handle_laser(i);
  }
  //Serial.println();
}

// Public
void setup_hal_sensors_ultrasonic() {
	_pingTimers[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    _pingTimers[i] = _pingTimers[i - 1] + SONAR_PING_INTERVAL;
}

void loop_hal_sensors_ultrasonic() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= _pingTimers[i]) {         // Is it this sensor's time to ping?
      _pingTimers[i] += SONAR_PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && _currentSensor == SONAR_NUM - 1) _sensors_ultrasonic_one_sensor_cycle(); // Sensor ping cycle complete, do something with the results.
      _sonars[_currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      _currentSensor = i;                          // Sensor being accessed.
      hal_sensors_ultrasonic_distances_cm[_currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      _sonars[_currentSensor].ping_timer(_sensors_ultrasonic_echo_check); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
}
