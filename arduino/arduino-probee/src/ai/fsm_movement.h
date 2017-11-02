// FSM Definition (see fsm_movement.png and config.h)

// Private

// IDLE ----------------------------------------------------------------------------
STATE_ENTER(idle) {

}

STATE_UPDATE(idle) {

}

STATE_EXIT(idle) {

}

// REASONING ----------------------------------------------------------------------------
STATE_ENTER(reasoning) {

}

STATE_UPDATE(reasoning) {

}

STATE_EXIT(reasoning) {

}

// STOP ----------------------------------------------------------------------------
STATE_ENTER(stop) {

}

STATE_UPDATE(stop) {

}

STATE_EXIT(stop) {

}

// FORWARD ----------------------------------------------------------------------------
STATE_ENTER(forward) {

}

STATE_UPDATE(forward) {

}

STATE_EXIT(forward) {

}

// SLOW FORWARD ----------------------------------------------------------------------------
STATE_ENTER(slow_forward) {

}

STATE_UPDATE(slow_forward) {

}

STATE_EXIT(slow_forward) {

}

// FAST FORWARD ----------------------------------------------------------------------------
STATE_ENTER(fast_forward) {

}

STATE_UPDATE(fast_forward) {

}

STATE_EXIT(fast_forward) {

}

// BACKWARD ----------------------------------------------------------------------------
STATE_ENTER(backward) {

}

STATE_UPDATE(backward) {

}

STATE_EXIT(backward) {

}

// SLOW BACKWARD ----------------------------------------------------------------------------
STATE_ENTER(slow_backward) {

}

STATE_UPDATE(slow_backward) {

}

STATE_EXIT(slow_backward) {

}

// SCANNING ----------------------------------------------------------------------------
STATE_ENTER(scanning) {

}

STATE_UPDATE(scanning) {

}

STATE_EXIT(scanning) {

}

// TURN LEFT ----------------------------------------------------------------------------
STATE_ENTER(turn_left) {
	hal_servo_stop_scanning(SCANNING_ALL);
	hal_servo_rotate_left();
}

STATE_UPDATE(turn_left) {

}

STATE_EXIT(turn_left) {
	hal_servo_start_scanning(SCANNING_FULL);
}

// TURN RIGHT ----------------------------------------------------------------------------
STATE_ENTER(turn_right) {
	hal_servo_stop_scanning(SCANNING_ALL);
	hal_servo_rotate_right();
}

STATE_UPDATE(turn_right) {

}

STATE_EXIT(turn_right) {
	hal_servo_start_scanning(SCANNING_FULL);
}

// Public
void setup_fsm_movement() {

}

void fsm_movement_loop() {
	UPDATE_FSM(movement);
}
