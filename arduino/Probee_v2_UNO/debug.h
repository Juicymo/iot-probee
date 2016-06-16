
// Macros
#ifdef DEBUG
#define TRACE(x) Serial.print(x);
#define TRACELN(x) Serial.println(x);
#else
#define TRACE(x)
#define TRACELN(x)
#endif

// Private

// Public
void setup_debug() {
	Serial.begin(9600);
	TRACELN("Setup");
}