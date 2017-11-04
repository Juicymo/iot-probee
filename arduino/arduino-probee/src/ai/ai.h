// Includes
#include "fsm_movement.h"
//#include "blackboard.h"
//#include "environment.h"
//#include "mas.h"

// Public
void setup_ai() {
	setup_fsm_movement();
}

void ai_loop() {
	fsm_movement_loop();
}
