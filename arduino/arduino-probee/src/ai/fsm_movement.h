// FSM Definition (see fsm_movement.png)
// States
DEFINE_STATE(idle);
DEFINE_STATE(reasoning);
DEFINE_STATE(stop);
DEFINE_STATE(forward);
DEFINE_STATE(slow_forward);
DEFINE_STATE(fast_forward);
DEFINE_STATE(backward);
DEFINE_STATE(slow_backward);
DEFINE_STATE(turn_left);
DEFINE_STATE(turn_right);

// Events
#define EVENT_FORWARD_OBSTACLE_NONE   	10
#define EVENT_FORWARD_OBSTACLE_FAR    	11
#define EVENT_FORWARD_OBSTACLE_NEAR   	12
#define EVENT_FORWARD_OBSTACLE_CLOSE    13
#define EVENT_FORWARD_OBSTACLE_BLOCKED  14

#define EVENT_BACKWARD_OBSTACLE_NONE   	20
#define EVENT_BACKWARD_OBSTACLE_FAR    	21
#define EVENT_BACKWARD_OBSTACLE_NEAR   	22
#define EVENT_BACKWARD_OBSTACLE_CLOSE   23
#define EVENT_BACKWARD_OBSTACLE_BLOCKED 24

INIT_FSM(movement, idle);

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

}

STATE_UPDATE(turn_left) {

}

STATE_EXIT(turn_left) {

}

// TURN RIGHT ----------------------------------------------------------------------------
STATE_ENTER(turn_right) {

}

STATE_UPDATE(turn_right) {

}

STATE_EXIT(turn_right) {

}

// Public
void setup_fsm_movement() {
	
}

void fsm_movement_loop() {
	UPDATE_FSM(movement);
}
