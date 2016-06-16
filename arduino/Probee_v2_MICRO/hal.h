
// HAL = Hardware Abstraction Layer
//#include "hal_lcd.h"
//#include "hal_i2c.h"
#include "hal_motor.h"
#include "hal_bluetooth.h"
//#include "hal_pir.h"
//#include "hal_servo.h"

void setup_hal() {
	setup_hal_motor();
	setup_hal_bluetooth();
}

// Private