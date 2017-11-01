// Macros
#define DEFINE_TASK(name)       unsigned long name##_tick;  \
                                void name##_loop();

#define INIT_TASK(name)         name##_tick = millis();

#define PERFORM_TASK(name, constant)       if ( millis() - name##_tick > constant ) {  \
                                              name##_loop();  \
                                              name##_tick = millis();  \
                                           };

// Private


// Public
