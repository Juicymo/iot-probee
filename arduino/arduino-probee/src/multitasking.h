// Private
//DEFINE_TASK(hal_bluetooth);
//DEFINE_TASK(state_machine);
//DEFINE_TASK(hal_i2c);
DEFINE_TASK(hal_servo);

// Public
void setup_multitasking() {
    //INIT_TASK(hal_bluetooth);
    //INIT_TASK(state_machine);
    //INIT_TASK(hal_i2c);
    INIT_TASK(hal_servo);
}

void loop_multitasking() {
    //PERFORM_TASK(hal_bluetooth, TICK_BLUETOOTH);
    //PERFORM_TASK(state_machine, TICK_STATE_MACHINE);
    //PERFORM_TASK(hal_i2c, TICK_I2C);
    PERFORM_TASK(hal_servo, TICK_SCANNING);
    PERFORM_TASK_ALWAYS(loop_hal_sensors_ultrasonic);
}
