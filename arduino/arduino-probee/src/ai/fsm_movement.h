// FSM Definition (see fsm_movement.png and config.h)

// Private

// IDLE ----------------------------------------------------------------------------
STATE_ENTER(idle) {
	//TRACELN("State: Idle");
	hal_lcd_print_state("Idle    ");
	fsm_is_idle = true;
	hal_servo_start_scanning(SCANNING_FULL);
}

STATE_UPDATE(idle) {

}

STATE_EXIT(idle) {
	hal_servo_stop_scanning(SCANNING_ALL);
	hal_servo_rotate_forward();
	fsm_is_idle = false;
}

// REASONING ----------------------------------------------------------------------------
long random_number;
STATE_ENTER(reasoning) {
	//TRACELN("State: Reasoning");
	hal_lcd_print_state("Thinking");
	hal_led_on(LED_REASONING);
}

STATE_UPDATE(reasoning) {
	byte forward_collision = hal_sensors_ultrasonic_collisions[SONAR_SENSOR_FORWARD];

	// for (uint8_t i = 0; i < SONAR_NUM; i++) {
  //   Serial.print(i);
  //   Serial.print("=");
  //   Serial.print(hal_sensors_ultrasonic_distances_cm[i]);
  //   Serial.print("cm ");
  // }
  // Serial.println();

	if (forward_collision == COLLISION_BLOCKED) {
		random_number = random(3); // 0 - 2

		if (random_number == 0) {
			fsm_movement.trigger(EVENT_REASONING_TURN_LEFT);
		}
		else if (random_number == 1) {
			fsm_movement.trigger(EVENT_REASONING_TURN_RIGHT);
		}
		else { // 2 = try to go backwards
			byte backward_collision = hal_sensors_ultrasonic_collisions[SONAR_SENSOR_BACKWARD];

			if (backward_collision == COLLISION_CLOSE) {
				fsm_movement.trigger(EVENT_REASONING_MOVE_SLOW_BACKWARD);
			}
			else if (
				backward_collision == COLLISION_NONE ||
				backward_collision == COLLISION_FAR ||
				backward_collision == COLLISION_NEAR
			) {
				fsm_movement.trigger(EVENT_REASONING_MOVE_BACKWARD);
			}
			else { // backward_collision == COLLISION_BLOCKED, cannot go back, turn instead
				random_number = random(2); // 0 - 1

				if (random_number == 0) {
					fsm_movement.trigger(EVENT_REASONING_TURN_LEFT);
				}
				else { // random_number == 1
					fsm_movement.trigger(EVENT_REASONING_TURN_RIGHT);
				}
			}
		}
	}
	else if (forward_collision == COLLISION_CLOSE) {
		fsm_movement.trigger(EVENT_REASONING_MOVE_SLOW_FORWARD);
	}
	else { // COLLISION_NONE || COLLISION_FAR || COLLISION_NEAR
		fsm_movement.trigger(EVENT_REASONING_MOVE_FORWARD);
	}
}

STATE_EXIT(reasoning) {
	hal_led_off(LED_REASONING);
}

// BRAKE ----------------------------------------------------------------------------
STATE_ENTER(brake) {
	//TRACELN("State: Brake");
	hal_lcd_print_state("Brake   ");
	hal_motor_brake(MOTOR_BOTH);
}

STATE_UPDATE(brake) {

}

STATE_EXIT(brake) {

}

// STOP ----------------------------------------------------------------------------
STATE_ENTER(stop) {
	//TRACELN("State: Stop");
	hal_lcd_print_state("Stop    ");
	hal_motor_stop(MOTOR_BOTH);
}

STATE_UPDATE(stop) {
	fsm_movement.trigger(EVENT_REASONING_STOPPED);
}

STATE_EXIT(stop) {

}

// FORWARD ----------------------------------------------------------------------------
STATE_ENTER(forward) {
	//TRACELN("State: Forward");
	hal_lcd_print_state("<<      ");
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_HALF);
}

STATE_UPDATE(forward) {

}

STATE_EXIT(forward) {

}

// SLOW FORWARD ----------------------------------------------------------------------------
STATE_ENTER(slow_forward) {
	//TRACELN("State: Slow Forward");
	hal_lcd_print_state("<       ");
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_QUATER);
}

STATE_UPDATE(slow_forward) {

}

STATE_EXIT(slow_forward) {

}

// FAST FORWARD ----------------------------------------------------------------------------
STATE_ENTER(fast_forward) {
	//TRACELN("State: Fast Forward");
	hal_lcd_print_state("<<<     ");
	hal_motor_drive(MOTOR_BOTH, MOTOR_SPEED_FULL);
}

STATE_UPDATE(fast_forward) {

}

STATE_EXIT(fast_forward) {

}

// BACKWARD ----------------------------------------------------------------------------
STATE_ENTER(backward) {
	//TRACELN("State: Backward");
	hal_lcd_print_state(">>      ");
	hal_motor_drive(MOTOR_BOTH, -MOTOR_SPEED_HALF);
}

STATE_UPDATE(backward) {

}

STATE_EXIT(backward) {

}

// SLOW BACKWARD ----------------------------------------------------------------------------
STATE_ENTER(slow_backward) {
	//TRACELN("State: Slow Backward");
	hal_lcd_print_state(">       ");
	hal_motor_drive(MOTOR_BOTH, -MOTOR_SPEED_QUATER);
}

STATE_UPDATE(slow_backward) {

}

STATE_EXIT(slow_backward) {

}

// TURN LEFT ----------------------------------------------------------------------------
STATE_ENTER(turn_left) {
	//TRACELN("State: Turn Right");
	hal_lcd_print_state("Right   ");
	hal_servo_stop_scanning(SCANNING_ALL);
	hal_servo_rotate_left();
	hal_motor_turn_left(MOTOR_SPEED_HALF);
}

STATE_UPDATE(turn_left) {

}

STATE_EXIT(turn_left) {
	//hal_servo_start_scanning(SCANNING_FULL);
	hal_servo_rotate_forward();
}

// TURN RIGHT ----------------------------------------------------------------------------
STATE_ENTER(turn_right) {
	//TRACELN("State: Turn Left");
	hal_lcd_print_state("Left    ");
	hal_servo_stop_scanning(SCANNING_ALL);
	hal_servo_rotate_right();
	hal_motor_turn_right(MOTOR_SPEED_HALF);
}

STATE_UPDATE(turn_right) {

}

STATE_EXIT(turn_right) {
	//hal_servo_start_scanning(SCANNING_FULL);
	hal_servo_rotate_forward();
}

// Public
void setup_fsm_movement() {
	// Move forward faster when no obstacles while moving
	TRANSITION(movement, forward, fast_forward, EVENT_FORWARD_OBSTACLE_NONE);

	TRANSITION(movement, slow_forward, forward, EVENT_FORWARD_OBSTACLE_NONE);
	TRANSITION(movement, slow_forward, forward, EVENT_FORWARD_OBSTACLE_FAR);
	TRANSITION(movement, slow_forward, forward, EVENT_FORWARD_OBSTACLE_NEAR);

	// Slow down when forward obstacle is near
  TRANSITION(movement, fast_forward, forward, EVENT_FORWARD_OBSTACLE_FAR);
	TRANSITION(movement, fast_forward, forward, EVENT_FORWARD_OBSTACLE_NEAR);
	TRANSITION(movement, fast_forward, slow_forward, EVENT_FORWARD_OBSTACLE_CLOSE);
	TRANSITION(movement, fast_forward, brake, EVENT_FORWARD_OBSTACLE_BLOCKED);

	TRANSITION(movement, forward, slow_forward, EVENT_FORWARD_OBSTACLE_CLOSE);
	TRANSITION(movement, forward, brake, EVENT_FORWARD_OBSTACLE_BLOCKED);

	TRANSITION(movement, slow_forward, brake, EVENT_FORWARD_OBSTACLE_BLOCKED);

	TRANSITION(movement, fast_forward, brake, EVENT_TURRET_OBSTACLE_BLOCKED);
	TRANSITION(movement, forward, brake, EVENT_TURRET_OBSTACLE_BLOCKED);
	TRANSITION(movement, slow_forward, brake, EVENT_TURRET_OBSTACLE_BLOCKED);
	
	// Move backward faster when no obstacles while moving
	TRANSITION(movement, slow_backward, backward, EVENT_FORWARD_OBSTACLE_NONE);
	TRANSITION(movement, slow_backward, backward, EVENT_BACKWARD_OBSTACLE_FAR);
	TRANSITION(movement, slow_backward, backward, EVENT_BACKWARD_OBSTACLE_NEAR);

  // Slow down when backward obstacle is near
	TRANSITION(movement, backward, slow_backward, EVENT_BACKWARD_OBSTACLE_CLOSE);
	TRANSITION(movement, backward, brake, EVENT_BACKWARD_OBSTACLE_BLOCKED);

	TRANSITION(movement, slow_backward, stop, EVENT_BACKWARD_OBSTACLE_BLOCKED);

	// Idle after stop
	TRANSITION(movement, stop, idle, EVENT_REASONING_STOPPED);

	// Reasoning transitions
	TRANSITION(movement, reasoning, forward, EVENT_REASONING_MOVE_FORWARD);
	TRANSITION(movement, reasoning, slow_forward, EVENT_REASONING_MOVE_SLOW_FORWARD);
	TRANSITION(movement, reasoning, backward, EVENT_REASONING_MOVE_BACKWARD);
	TRANSITION(movement, reasoning, slow_backward, EVENT_REASONING_MOVE_SLOW_BACKWARD);
	TRANSITION(movement, reasoning, turn_left, EVENT_REASONING_TURN_LEFT);
	TRANSITION(movement, reasoning, turn_right, EVENT_REASONING_TURN_RIGHT);

	// React to obstacles while idle
	TRANSITION(movement, idle, reasoning, EVENT_FORWARD_OBSTACLE_CLOSE);
	TRANSITION(movement, idle, reasoning, EVENT_FORWARD_OBSTACLE_BLOCKED);
	TRANSITION(movement, idle, reasoning, EVENT_BACKWARD_OBSTACLE_CLOSE);
	TRANSITION(movement, idle, reasoning, EVENT_BACKWARD_OBSTACLE_BLOCKED);

	// Stop turning on collision
	TRANSITION(movement, turn_right, stop, EVENT_TURRET_OBSTACLE_PRESENT);
	TRANSITION(movement, turn_left, stop, EVENT_TURRET_OBSTACLE_PRESENT);
	TRANSITION(movement, turn_right, stop, EVENT_TURRET_OBSTACLE_BLOCKED);
	TRANSITION(movement, turn_left, stop, EVENT_TURRET_OBSTACLE_BLOCKED);

	// Stop after braking
	TIMED_TRANSITION(movement, brake, stop, 100);

	// Stop turning after given interval
	TIMED_TRANSITION(movement, turn_right, stop, 2000);
	TIMED_TRANSITION(movement, turn_left, stop, 2000);

	// Start reasoning when idle for too long
	TIMED_TRANSITION(movement, idle, reasoning, 5000);

	// Start idle when moving forward for too long
	TIMED_TRANSITION(movement, slow_backward, stop, 1000);
	TIMED_TRANSITION(movement, backward, stop, 1000);
	TIMED_TRANSITION(movement, forward, stop, 10000);
	TIMED_TRANSITION(movement, fast_forward, stop, 10000);
}

void fsm_movement_loop() {
	UPDATE_FSM(movement);
}
