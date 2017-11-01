// Includes
// HAL = Hardware Abstraction Layer
//#include "hal_lcd.h"
#include "hal_i2c.h"
#include "hal_motor.h"
#include "hal_bluetooth.h"
//#include "hal_pir.h"
#include "hal_servo.h"
#include "hal_sensors_ultrasonic.h"
//#include "hal_sensors_infrared.h"

// Private

// Public
void setup_hal() {
	setup_hal_motor();
	//setup_hal_bluetooth();
	setup_hal_servo();
	//setup_hal_sensors_ultrasonic();
	//setup_hal_sensors_infrared();
  //setup_hal_i2c();
}
