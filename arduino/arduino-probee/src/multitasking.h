// Private
//DEFINE_TASK(hal_bluetooth);
//DEFINE_TASK(hal_i2c);
DEFINE_TASK(ai);
DEFINE_TASK(hal_servo);

// Public
void setup_multitasking() {
    //INIT_TASK(hal_bluetooth);
    //INIT_TASK(hal_i2c);
    INIT_TASK(ai);
    INIT_TASK(hal_servo);
}

void loop_multitasking() {
    //PERFORM_TASK(hal_bluetooth, TICK_BLUETOOTH);
    //PERFORM_TASK(hal_i2c, TICK_I2C);
    PERFORM_TASK(hal_servo, TICK_SCANNING);
    PERFORM_TASK(ai, TICK_AI);
    PERFORM_TASK_ALWAYS(loop_hal_sensors_ultrasonic);
}
