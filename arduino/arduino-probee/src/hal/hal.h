// Includes
// HAL = Hardware Abstraction Layer
//#include "hal_lcd.h"
#include "hal_i2c.h"
#include "hal_motor.h"
#include "hal_bluetooth.h"
//#include "hal_pir.h"
#include "hal_servo.h"
#include "hal_laser.h"
#include "hal_led.h"
#include "hal_sensors_ultrasonic.h"
//#include "hal_sensors_infrared.h"
#include "hal_lcd.h"
#include "hal_pixy.h"

// Private

// Public
void setup_hal() {
	setup_hal_motor();
	//setup_hal_bluetooth();
	//setup_hal_servo();
	setup_hal_laser();
	setup_hal_led();
	setup_hal_lcd();
	setup_hal_sensors_ultrasonic();
	//setup_hal_sensors_infrared();
  //setup_hal_i2c();
  setup_hal_pixy();
}
