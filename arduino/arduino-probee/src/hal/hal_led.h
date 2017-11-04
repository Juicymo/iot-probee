// Private

// Public
void hal_led_on(byte led) {
	if (led == LED_REASONING) {
		digitalWrite(LED_REASONING_PIN, HIGH);
	}
}

void hal_led_off(byte led) {
	if (led == LED_REASONING) {
		digitalWrite(LED_REASONING_PIN, LOW);
	}
}

void setup_hal_led() {
	pinMode(LED_REASONING_PIN, OUTPUT);
	hal_led_off(LED_REASONING);
}
