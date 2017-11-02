// Macros
#define DEFINE_STATE(name)  void _on_state_##name##_enter();  \
                            void _on_state_##name##_update(); \
                            void _on_state_##name##_exit();   \
                            State state_##name(&_on_state_##name##_enter, &_on_state_##name##_update, &_on_state_##name##_exit);

#define STATE_ENTER(name)   void _on_state_##name##_enter()
#define STATE_UPDATE(name)  void _on_state_##name##_update()
#define STATE_EXIT(name)    void _on_state_##name##_exit()

#define INIT_FSM(name, default_state)    Fsm fsm_##name(&state_##default_state)

#define UPDATE_FSM(name)    fsm_##name.run_machine()
