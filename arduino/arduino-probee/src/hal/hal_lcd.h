// Private

// Public
LiquidCrystal_PCF8574 lcd(LCD_I2C_ADDRESS);

void hal_lcd_clear_line_1() {
  lcd.home();
  //         1234567812345678
  lcd.print("                ");
}

void hal_lcd_clear_line_2() {
  lcd.setCursor(0, 1);
  //         1234567812345678
  lcd.print("                ");
}

void hal_lcd_print_distances(unsigned int front, unsigned int back) {
  lcd.setCursor(0, 0);
  //         1234567812345678
  //lcd.print(turret);
  //lcd.print("cm ");

  lcd.setCursor(0, 1);
  lcd.print(front);
  lcd.print("cm ");

  lcd.setCursor(8, 1);
  lcd.print(back);
  lcd.print("cm ");
}

void hal_lcd_print_state(String state) {
  lcd.setCursor(8, 0);
  //         1234567812345678
  lcd.print(state);
}

void hal_lcd_welcome() {
  //         1234567812345678
  lcd.clear();
  lcd.home();
  lcd.print("     Hello,     ");
  lcd.setCursor(0, 1);
  lcd.print("  I am #Probee  ");
  delay(3000);

  lcd.clear();
  lcd.home();
  lcd.print("      Dr.       ");
  lcd.setCursor(0, 1);
  lcd.print("    Chandra,    ");
  delay(3000);

  lcd.clear();
  lcd.home();
  lcd.print(" I am prepared  ");
  lcd.setCursor(0, 1);
  lcd.print(" for my lesson. ");
  delay(3000);

  lcd.clear();
}

void setup_hal_lcd() {
	lcd.begin(16, 2);
	lcd.setBacklight(255);
  lcd.clear();
}

void hal_lcd_loop() {
  hal_lcd_print_distances(
		hal_sensors_ultrasonic_distances_cm[SONAR_SENSOR_FORWARD],
		hal_sensors_ultrasonic_distances_cm[SONAR_SENSOR_BACKWARD]
	);
}
