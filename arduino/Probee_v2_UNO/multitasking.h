
// Macros
#define DEFINE_TASK(name)       unsigned long name##_tick;  \
                                void name##_loop();

#define INIT_TASK(name)         name##_tick = millis();

#define PERFORM_TASK(name, constant)       if ( millis() - name##_tick > constant ) {  \
                                              name##_loop();  \
                                              name##_tick = millis();  \
                                           };

// Private
//DEFINE_TASK(hal_bluetooth);
//DEFINE_TASK(state_machine);
DEFINE_TASK(hal_i2c);

// Public
void setup_multitasking() {
    //INIT_TASK(hal_bluetooth);
    //INIT_TASK(state_machine);
    INIT_TASK(hal_i2c);
}

void loop_multitasking() {
    //PERFORM_TASK(hal_bluetooth, SPEED_BLUETOOTH);
    //PERFORM_TASK(state_machine, SPEED_STATE_MACHINE);
    PERFORM_TASK(hal_i2c, SPEED_I2C);
}
