#include <Arduino.h>

// Inbuilt Libraries
//#include <Bounce.h>
#include <Servo.h>
#include <Wire.h>

// External Libraries
#include <Fsm.h>

// Custom Libraries
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#define PROBEE_DEBUG
#include "serial.h"
#include "debug.h"

#include "config.h"

#include "macros/macros.h"
#include "hal/hal.h"
//#include "ai/ai.h"

#include "multitasking.h"

void setup() {
	setup_serial();
	setup_debug();
	setup_hal();
	//setup_state_machine();
	//setup_mas();
	setup_multitasking();
}

void loop() {
	loop_multitasking();
	delay(10);
}
