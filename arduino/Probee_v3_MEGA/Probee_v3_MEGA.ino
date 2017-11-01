// Official Libraries
//#include <Bounce.h>
#include <Servo.h>
#include <Wire.h>
#include <FiniteStateMachine.h>

// Custom Libraries
//#include <LiquidCrystal_I2C.h>

#define DEBUG
#include "debug.h"

#include "config.h"

//#include "fsm.h"
#include "hal.h"
//#include "state_machine.h"
//#include "blackboard.h"
//#include "environment.h"
//#include "mas.h"
#include "multitasking.h"

void setup() {
	setup_debug();
	setup_hal();
	//setup_state_machine();
	//setup_mas();
	setup_multitasking();
}

void loop() {
	loop_multitasking();
  delay(100);
}
