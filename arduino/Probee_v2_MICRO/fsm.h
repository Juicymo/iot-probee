
#define NEW_STATE(name)     void name##_enter();  \
							void name##_update(); \
							void name##_exit();   \
							State name = State(name##_enter, name##_update, name##_exit);

#define STATE_ENTER(name)   void name##_enter()
#define STATE_UPDATE(name)  void name##_update()
#define STATE_EXIT(name)    void name##_exit()