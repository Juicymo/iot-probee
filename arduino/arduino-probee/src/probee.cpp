#include <Arduino.h>

// Inbuilt Libraries
//#include <Bounce.h>
#include <Servo.h>
#include <Wire.h>

// External Libraries
#include <Fsm.h>

// Custom Libraries
#include <LiquidCrystal_PCF8574.h>
//#include <LiquidMenu.h>
#include <NewPing.h>

#define PROBEE_DEBUG
#include "serial.h"
#include "debug.h"
#include "random.h"

#include "macros/macros.h"

#include "config.h"

#include "hal/hal.h"
#include "ai/ai.h"

#include "multitasking.h"

void setup() {
	setup_serial();
	setup_debug();
	setup_random();
	setup_hal();
	setup_ai();
	//setup_mas();
	setup_multitasking();

	hal_lcd_welcome();
}

void loop() {
	loop_multitasking();
}
