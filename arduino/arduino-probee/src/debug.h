// Macros
#ifdef PROBEE_DEBUG
#define TRACE(x) Serial.print(x);
#define TRACELN(x) Serial.println(x);
#define WARNING(x) Serial.print("Warning: "); Serial.println(x);
#define ERROR(x) Serial.print("Error: "); Serial.println(x);
#else
#define TRACE(x)
#define TRACELN(x)
#define WARNING(x)
#define ERROR(x)
#endif

// Private

// Public
void setup_debug() {
	//TRACELN("Setup");
}
