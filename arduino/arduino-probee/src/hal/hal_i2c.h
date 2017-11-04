// Private
int number = 0;
void hal_i2c_send() {
  //Wire.write("hello "); // respond with message of 6 bytes as expected by master
  Wire.write(number);
}

void hal_i2c_receive(int byteCount) {
  while(Wire.available()) {
    number = Wire.read();
    Serial.print("data received ");
    Serial.println(number);
  }

  if (number == 1) {
    Serial.println("i2c action taken");
  }
}

// Public
void setup_hal_i2c() {
	Wire.begin(I2C_ADDRESS);         // join i2c bus with address I2C_ADDRESS
  Wire.onRequest(hal_i2c_send);    // register events
  Wire.onReceive(hal_i2c_receive);
}

void hal_i2c_loop() {
//  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
//
//  while (Wire.available()) { // slave may send less than requested
//    char c = Wire.read(); // receive a byte as character
//    Serial.print(c);         // print the character
//  }
}
