#include <Servo.h> 
#include <Wire.h>
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
//#include <LiquidCrystal_SI2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
//#include <SI2CIO.h>
//#include <SoftI2CMaster.h>

// ----------------------------- CONSTANTS -----------------------------
#define M_L 1
#define M_R 2

#define M_PWM_L 6
#define M_PWM_R 5
#define M_L1 9
#define M_L2 10
#define M_R1 7
#define M_R2 8

#define SONAR_ECHO 2
#define SONAR_TRIGR	A0

#define SONAR_ERR_BCK_ECHO 3
#define SONAR_ERR_BCK_TRIGR	A1

#define SONAR_ERR_FWD_ECHO 4
#define SONAR_ERR_FWD_TRIGR	A2

#define SERVO_PIN 11

#define SONAR_STEPS 50
#define SONAR_MIN 20
#define SONAR_MAX 120
#define SONAR_STEP (256 - ((256 - SONAR_MAX) + SONAR_MIN)) / SONAR_STEPS

#define SONAR_SPEED 50
#define SENSORS_SPEED 50
#define REASONING_SPEED 100
#define LCD_SPEED 500

#define FWD_SAFE_DIST 20
#define BWD_SAFE_DIST 15

#define ROBOT_SPEED_TURN 1.0
#define ROBOT_SPEED_FULL 1.0
#define ROBOT_SPEED_HALF 0.8
#define ROBOT_SPEED_QUATER 0.6

#define FORWARD_ROT 64

#define LEFT_TURN_DIST_LIMIT 4
#define RIGHT_TURN_DIST_LIMIT 4

#define MODE_SCAN 0
#define MODE_FREE_SPACE 1
#define MODE_WALL_FOLLOW 2
#define MODE_IDLE 3

#define IR_RIGHT 12
#define IR_LEFT 13

#define TURN_STEPS 1000
#define BACK_STEPS 200

#define SCAN_PAUSE 2000

#define MOVE_FAST_FWD_SAFE_DIST 100
#define MOVE_NORM_FWD_SAFE_DIST 50
#define MOVE_SLOW_FWD_SAFE_DIST 30

Servo servo;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

unsigned long sonar_measure;
unsigned long sensors_measure;
unsigned long reasoning_measure;
unsigned long lcd_measure;
unsigned long lcd_measure1;
unsigned long lcd_measure2;
unsigned long lcd_measure3;
unsigned long lcd_measure4;

long randNumber;

// ----------------------------- SETUP -----------------------------
void setup()
{
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.backlight();

  pinMode(M_L1, OUTPUT);
  pinMode(M_L2, OUTPUT);
  pinMode(M_R1, OUTPUT);
  pinMode(M_R2, OUTPUT);
  pinMode(M_PWM_L, OUTPUT);
  pinMode(M_PWM_R, OUTPUT);

  motor(M_L, 0);
  motor(M_R, 0);
  
  pinMode(SONAR_TRIGR, OUTPUT);
  pinMode(SONAR_ECHO, INPUT);

  pinMode(SONAR_ERR_BCK_TRIGR, OUTPUT);
  pinMode(SONAR_ERR_BCK_ECHO, INPUT);

  pinMode(SONAR_ERR_FWD_TRIGR, OUTPUT);
  pinMode(SONAR_ERR_FWD_ECHO, INPUT);
  
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  servo.attach(SERVO_PIN);
  servo.write(FORWARD_ROT);

  lcd.setCursor(5,0); //Start at character 1 on line 0
  lcd.print("Hello,");
  
  lcd.setCursor(2,1);
  lcd.print("Mr. Chandra");

  delay(2000);

  lcd.setCursor(3,0);
  lcd.print("I am ready");
  
  lcd.setCursor(1,1);
  lcd.print("for our lesson");
  
  delay(2000);
  
  lcd.setCursor(0, 1);
  lcd.print("cm              ");
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(3));

  // Init measures
  sonar_measure = millis();
  sensors_measure = millis();
  reasoning_measure = millis();
  lcd_measure = millis();
  lcd_measure1 = millis();
  lcd_measure2 = millis();
  lcd_measure3 = millis();
  lcd_measure4 = millis();
}

// ----------------------------- MAIN LOOP -----------------------------
void loop()
{	
  environment_loop();
}

// ----------------------------- VARIABLES -----------------------------

// System
int pos = 0;           // rotation position of the servo with the main ultrasonic sensor
bool dir = true;       // current doration direction if the servo with the main ultrasonic sensor
float val = 0;         // last measured distance value by the main ultrasonic sensor (in cm)
float fwd_barrier = 0; // last measured distance value by the front fixed ultrasonic sensor (in cm)
float bwd_barrier = 0; // last measured distance value by the back fixed ultrasonic sensor (in cm)
bool sonar_turn = true;
bool turning = false;

bool left_obts = false;
bool right_obts = false;

// ugly naive solution for left/right turn reasoning
float val_left1 = -1;
float val_left2 = -1;
float val_left3 = -1;
float val_left4 = -1;
float val_left5 = -1;
float val_right1 = -1;
float val_right2 = -1;
float val_right3 = -1;
float val_right4 = -1;
float val_right5 = -1;
float val_fwd = -1;

// Blackboard (only one agent writes, all can read) = to "a1_" prefixed vars only agent 1 can write...
bool a1_has_message = false;
bool a1_no_forward = true;
bool a1_no_backward = true;
bool a2_has_message = false;
float a2_mL = 0.0;
float a2_mR = 0.0;
bool a3_has_message = false;
float a3_mL = 0.0;
float a3_mR = 0.0;
bool a3_sig_scan_reset = false;
bool a3_sig_wait_for_new_scan_one = false;
bool a3_sig_wait_for_new_scan_both = false;
bool a3_sig_no_fwd_again = false;
int a3_sig_no_look = 0;

int a3_mode = MODE_SCAN;
int a3_last_mode = MODE_FREE_SPACE;
int a3_free_mode = 0;
int a3_free_step_counter = 0;
int a3_wall_mode = 0;

// ----------------------------- AGENTS -----------------------------

// A1 - Stoping Agent
// Responsibility: Prevent further car movement fwd or bwd if obstacle is in the way
bool a1_wants_action()
{
  a1_has_message = false;
  
  return true;
}

void a1_reasoning_loop()
{
  float bwd_safe_dist = BWD_SAFE_DIST;
  float fwd_safe_dist = FWD_SAFE_DIST;
  
  // path is clear
  a1_no_forward = false;
  a1_no_backward = false;
  
  // check
  if (fwd_barrier <= fwd_safe_dist || left_obts == true || right_obts == true) {
    a1_no_forward = true;
  }
  if (bwd_barrier <= bwd_safe_dist) {
    a1_no_backward = true;
  }
  
  if (millis() - lcd_measure > LCD_SPEED) {
    lcd.setCursor(10, 0);
    lcd.print("      ");
    if (a1_no_forward && a1_no_backward) {
      lcd.setCursor(10, 0);
      lcd.print(" BLCKD");
    }
    else if (a1_no_forward) {
      lcd.setCursor(10, 0);
      lcd.print("NO FWD");
    }
    else if (a1_no_backward) {
      lcd.setCursor(10, 0);
      lcd.print("NO BWD");
    }
    else {
      lcd.setCursor(10, 0);
      lcd.print(" CLEAR");
    }
  
    lcd_measure = millis();
  }
  
  a1_has_message = a1_no_forward || a1_no_backward;
}

// A2 - Communication Agent
// Responsibility: Load commands from bluetooth and pass them to moving agent (and send main sensor values to bluetooth)
bool a2_wants_action()
{
  a2_has_message = false;
  
  return (Serial.available() > 0);
}

void a2_reasoning_loop()
{
  byte cmd = Serial.read();
  
  if (cmd == 'M') {
    a2_mL = Serial.parseFloat();
    a2_mR = Serial.parseFloat();
    a2_has_message = true;
  }
  else {
    a2_mL = 0.0;
    a2_mR = 0.0;
    a2_has_message = false;
  }

  cmd = 0;
}

// A3 - Planning Agent
// Responsibility: Plan the next autonomous move
bool a3_wants_action()
{
  a3_has_message = false;
  
  if (millis() - lcd_measure1 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("          ");
    
    if (a2_has_message) {
      lcd.setCursor(0, 0);
      lcd.print("A2: Wrkng");
    }
  
    lcd_measure1 = millis();
  }
  
  return !a2_has_message; // when communicating agent has command, there is no need for reasoning (this way commands take precedence)
}

void a3_reasoning_loop() // currently implemented as finite state machine ...
{
  a3_has_message = true;
  
  if (a3_mode == MODE_SCAN) {
    a3_reasoning_idle(); // robot is not moving when scaning ...
    
    lcd.setCursor(0, 0);
    lcd.print("A3: Scan ");
    
    if (a3_sig_scan_reset == false) { // Start smart look if none is running
      a3_sig_scan_reset = true;
      a3_sig_wait_for_new_scan_one = false;
      a3_sig_wait_for_new_scan_both = false;
    }
    
    if (a3_sig_scan_reset == true && a3_sig_wait_for_new_scan_one == true && a3_sig_wait_for_new_scan_both == true) { // Change mode when done
      a3_sig_scan_reset = false;
       
      sonar_reset_position();
      a3_sig_no_look = SCAN_PAUSE;
      
      a3_reasoning_continue_previous_mode();
    }
  }
  else if (a3_mode == MODE_FREE_SPACE) {
    if (a3_free_mode == 0) { // think
      a3_reasoning_think(); // robot is not moving when thinking ...
      
      bool ok = false;
      while (!ok) {
        ok = true;
        
        randNumber = random(4); // 0..1
        
        if (randNumber == 0) { // turn
          float left_val = a3_reasoning_compute_left_turn_barrier();
          float right_val = a3_reasoning_compute_right_turn_barrier();
          
          if (left_val <= LEFT_TURN_DIST_LIMIT && right_val <= RIGHT_TURN_DIST_LIMIT) { // we cannot turn
            ok = false;
          }
          else if (right_val < left_val) { // we have more space on left
            if (left_val > LEFT_TURN_DIST_LIMIT) { // can we turn left?
              a3_free_mode = 3; // lets turn left
              a3_free_step_counter = TURN_STEPS;
            }
            else if (right_val > RIGHT_TURN_DIST_LIMIT) { // can we turn right?
              a3_free_mode = 4; // lets turn right
              a3_free_step_counter = TURN_STEPS;
            }
            else { // lets try something other...
              ok = false;
            }
          }
          else { // we have more space on right
            if (right_val > RIGHT_TURN_DIST_LIMIT) { // can we turn right?
              a3_free_mode = 4; // lets turn right
              a3_free_step_counter = TURN_STEPS;
            } 
            else if (left_val > LEFT_TURN_DIST_LIMIT) { // can we turn left?
              a3_free_mode = 3; // lets turn left
              a3_free_step_counter = TURN_STEPS;
            }
            else { // lets try something other...
              ok = false;
            }
          }
        }
        else { // move
          if (a1_no_backward == true && a1_no_forward == true) { // we are blocked
            ok = false;
          }
          else if ((a1_no_backward == false && a1_no_forward == false) || (a1_no_backward == true && a1_no_forward == false)) { // we can move freely or forward only
            a3_free_mode = 1; // lets go forward
          }
          else  { // we can move backward only
            a3_free_mode = 2; // lets go backward
            a3_free_step_counter = BACK_STEPS;
          }
        }
      }
    }
    else if (a3_free_mode == 1) { // move forward till obstacle
      if (/*a3_free_step_counter <= 0 || */a1_no_forward == true) {
        a3_free_mode = 0; // think
        
        //a3_reasoning_may_scan();
      }
      else {
        if (val_fwd > MOVE_FAST_FWD_SAFE_DIST && fwd_barrier > MOVE_FAST_FWD_SAFE_DIST) { // fast forward
          a3_reasoning_fast_forward();
        }
        else if (val_fwd > MOVE_NORM_FWD_SAFE_DIST && fwd_barrier > MOVE_NORM_FWD_SAFE_DIST) { // forward
          a3_reasoning_forward();
        }
        else { // slow forward
          a3_reasoning_slow_forward();
        }
        
        //a3_free_step_counter =- 1;
      }
    }
    else if (a3_free_mode == 2) { // move backward for desired amount of steps (or till obstacle)
      if (a3_free_step_counter <= 0 || a1_no_backward == true) {
        a3_free_mode = 0; // think
        
        //a3_reasoning_may_scan();
      }
      else {
        a3_reasoning_backward();
        
        a3_free_step_counter =- 1;
      }
    }
    else if (a3_free_mode == 3) { // turn left
      if (a3_free_step_counter <= 0) {
        a3_free_mode = 0; // think
      }
      else {
        a3_reasoning_turn_left();
        
        a3_free_step_counter =- 1;
      }
    }
    else if (a3_free_mode == 4) { // turn right
      if (a3_free_step_counter <= 0) {
        a3_free_mode = 0; // think
      }
      else {
        a3_reasoning_turn_right();
        
        a3_free_step_counter =- 1;
      }
    }
    else { // idle
      a3_reasoning_idle();
    }
  }
  else if (a3_mode == MODE_WALL_FOLLOW) {
    if (a3_wall_mode == 0) { // scan weather left or right wall is closer
      
    }
    else if (a3_wall_mode == 1) { // follow right wall
      
    }
    else if (a3_wall_mode == 2) { // follow left wall
      
    }
  }
  else { // MODE_IDLE
    a3_reasoning_idle();
  }
}

// ----- Mode Change -----
void a3_reasoning_continue_previous_mode() {
  a3_mode = a3_last_mode;
  
  if (a3_mode == MODE_FREE_SPACE) {
    sonar_start_scan();
  }
}

void a3_reasoning_may_scan() {
  a3_sig_no_look =- 1;
        
  if (a3_sig_no_look <= 0) {
    a3_reasoning_start_scan();
  }
}

void a3_reasoning_start_scan() {
  sonar_start_scan();
  
  a3_last_mode = a3_mode;
  
  a3_mode = MODE_SCAN;
}

void a3_reasoning_start_free_space() {
  sonar_start_scan();
  
  a3_last_mode = a3_mode;
  
  a3_mode = MODE_FREE_SPACE;
  a3_free_mode = 0; // start with think
}

void a3_reasoning_start_wall_follow() {
  a3_last_mode = a3_mode;
  
  a3_mode = MODE_WALL_FOLLOW;
  a3_wall_mode = 0; // start with scan
}

void a3_reasoning_start_idle() {
  a3_last_mode = a3_mode;
  
  a3_mode = MODE_IDLE;
}

// ----- Actions -----
float a3_reasoning_compute_left_turn_barrier() {
  return (val_left1 + val_left2 + val_left3 + val_left4 + val_left5) / 5;
}

float a3_reasoning_compute_right_turn_barrier() {
  return (val_right1 + val_right2 + val_right3 + val_right4 + val_right5) / 5;
}

void a3_reasoning_turn() {
  // Compute if there is an obstacle on left or right
  float left_val = a3_reasoning_compute_left_turn_barrier();
  float right_val = a3_reasoning_compute_right_turn_barrier();
  
  if (left_val > right_val) {
    if (left_val > LEFT_TURN_DIST_LIMIT) {
      a3_reasoning_turn_left();
    }
    else {
      a3_reasoning_idle();
    }
  }
  else {
    if (right_val > RIGHT_TURN_DIST_LIMIT) {
      a3_reasoning_turn_right();
    }
    else {
      a3_reasoning_idle();
    }
  }
  
  a3_sig_no_fwd_again = false;
}

void a3_reasoning_turn_left() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Trn L ");
    
    lcd_measure3 = millis();
  }
  
  turning = true;
  a3_mL = -ROBOT_SPEED_TURN;
  a3_mR = ROBOT_SPEED_TURN;
}

void a3_reasoning_turn_right() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Trn R ");
    
    lcd_measure3 = millis();
  }
  
  turning = true;
  a3_mL = ROBOT_SPEED_TURN;
  a3_mR = -ROBOT_SPEED_TURN;
}

void a3_reasoning_fast_forward() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: FF    ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = ROBOT_SPEED_FULL;
  a3_mR = ROBOT_SPEED_FULL;
}

void a3_reasoning_forward() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Fwd   ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = ROBOT_SPEED_HALF;
  a3_mR = ROBOT_SPEED_HALF;
}

void a3_reasoning_slow_forward() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: SLFwd ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = ROBOT_SPEED_QUATER;
  a3_mR = ROBOT_SPEED_QUATER;
}

void a3_reasoning_backward() {
  a3_sig_no_fwd_again = true;
    
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Bwd   ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = -ROBOT_SPEED_HALF;
  a3_mR = -ROBOT_SPEED_HALF;
}

void a3_reasoning_think() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Think ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = 0.0;
  a3_mR = 0.0;
}

void a3_reasoning_idle() {
  if (millis() - lcd_measure3 > LCD_SPEED) {
    lcd.setCursor(0, 0);
    lcd.print("A3: Idle  ");
    
    lcd_measure3 = millis();
  }
  
  turning = false;
  a3_mL = 0.0;
  a3_mR = 0.0;
}

// A4 - Moving Agent
// Responsibility: Based on instructions from other agents control the robot movement
bool a4_wants_action()
{
  return a1_has_message || a2_has_message || a3_has_message;
}

void a4_reasoning_loop()
{
  float mlv = 0.0;
  float mrv = 0.0;
  
  // Step 1 - find out which instructions we should use
  if (a2_has_message) { // lets use communicating agent instructions
    mlv = a2_mL;
    mrv = a2_mR;
  }
  else if (a3_has_message) { // lets use planning agent instructions
    mlv = a3_mL;
    mrv = a3_mR;
  }
  else { // no instructions = stop the robot
    mlv = 0.0;
    mrv = 0.0;
  }
  
  // Step 2 - Adjust the instructions based on orders from stopping agent
  if (a1_has_message) {
    if (mlv > 0 && mrv > 0 && a1_no_forward) {
       mlv = 0.0;
       mrv = 0.0;
    }
    else if (mlv < 0 && mrv < 0 && a1_no_backward) {
       mlv = 0.0;
       mrv = 0.0;
    }
  }  
  
  // Step 3 - Fetch adjusted (= sanitized) instructions to the motors
  motor(M_L, mlv);
  motor(M_R, mrv);
  
  int rn = random(100) + 200; // 200..300
  
  // If turn left or right, make turning little but longer
  if (turning == true && mlv > 0 && mrv > 0) {
    delay(rn);
  }
}

// ----------------------------- ENVIRONMENT -----------------------------
void environment_loop()
{
  if (millis() - sonar_measure > SONAR_SPEED) {
    sonar_loop();
    sonar_measure = millis();
  }
  
  if (millis() - sensors_measure > SENSORS_SPEED) {
    sensors_loop();
    sensors_measure = millis();
  }
  
  if (millis() - reasoning_measure > REASONING_SPEED) {
    reasoning_loop();
    reasoning_measure = millis();
  }
}

// ----------------------------- LOOPS -----------------------------
void reasoning_loop()
{
  if (a1_wants_action()) {
    a1_reasoning_loop();
  }
  if (a2_wants_action()) {
    a2_reasoning_loop();
  }
  if (a3_wants_action()) {
    a3_reasoning_loop();
  }
  if (a4_wants_action()) {
    a4_reasoning_loop();
  }
}

void sensors_loop()
{
  collision_chck();
}

void sonar_loop()
{
  //Serial.print("S ");
  //Serial.print(pos);
  //Serial.print(" ");

  val = sonar_perform_measure();

  //Serial.println(val);

  if (millis() - lcd_measure4 > LCD_SPEED) {
    lcd.setCursor(3, 1);
    lcd.print(val);
    
    lcd_measure4 = millis();
  }
  
  if (pos == 0) {
    a3_sig_wait_for_new_scan_one = true;
    val_right1 = val;
  }
  else if (pos == 1) {
    val_right2 = val;
  }
  else if (pos == 2) {
    val_right3 = val;
  }
  else if (pos == 3) {
    val_right4 = val;
  }
  else if (pos == 4) {
    val_right5 = val;
  }
  else if (pos == 50) {
    a3_sig_wait_for_new_scan_both = true;
    val_left1 = val;
  }
  else if (pos == 49) {
    val_left2 = val;
  }
  else if (pos == 48) {
    val_left3 = val;
  }
  else if (pos == 47) {
    val_left4 = val;
  }
  else if (pos == 46) {
    val_left5 = val;
  }
  else if (pos == 25) {
    val_fwd = val;
    Serial.print("FWD ");
    Serial.println(val_fwd);
  }

  int val = (SONAR_MIN + pos * SONAR_STEP);
  
  if (sonar_turn) {
    servo.write(val);
  	
    pos += dir ? 1 : (-1);
  }
  
  if (pos >= SONAR_STEPS) {
    dir = false;
  }
  else if (pos <= 0) {
    dir = true;
  }
}

/*void motor_loop()
{
  if (Serial.available() > 0) {
    byte cmd = Serial.read();
    
    if (cmd == 'M') {
      float l = Serial.parseFloat();
      float r = Serial.parseFloat();
      
      motor(M_L, l);
      motor(M_R, r);
    }
  
    cmd = 0;
  }
}*/

// ----------------------------- UTILS -----------------------------
void sonar_start_scan() {
  sonar_turn = true;
}

void sonar_reset_position() {
  sonar_turn = false;
  servo.write(FORWARD_ROT);
}

float sonar_perform_measure()
{
  digitalWrite(SONAR_TRIGR, LOW); 
  delayMicroseconds(2); 
    
  digitalWrite(SONAR_TRIGR, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(SONAR_TRIGR, LOW);
  float duration = pulseIn(SONAR_ECHO, HIGH, 30 * 1000);
  
  //Calculate the distance (in cm) based on the speed of sound.
  float distance = duration/58.2;
  
  return distance;
}

void collision_chck()
{
  lcd.setCursor(10, 1); //Start at character 1 on line 0
  
  fwd_barrier = chck_err_fwd();
  bwd_barrier = chck_err_bck();
  
  left_obts = !digitalRead(IR_LEFT);
  right_obts = !digitalRead(IR_RIGHT);
  
  float bwd_safe_dist = BWD_SAFE_DIST;
  float fwd_safe_dist = FWD_SAFE_DIST;
  
  if (millis() - lcd_measure2 > LCD_SPEED) {
    if (fwd_barrier <= bwd_barrier) {
      if (fwd_barrier <= fwd_safe_dist) {
        lcd.print("FWD ER");
      }
      else {
        lcd.print("F      ");
        lcd.setCursor(11, 1);
        lcd.print(fwd_barrier);
      }
    }
    else {
      if (bwd_barrier <= bwd_safe_dist) {
        lcd.print("BWD ER");
      }
      else {
        lcd.print("B      ");
        lcd.setCursor(11, 1);
        lcd.print(bwd_barrier);
      }
    }
  
    lcd_measure2 = millis();
  }
}

float chck_err_fwd()
{
  digitalWrite(SONAR_ERR_FWD_TRIGR, LOW); 
  delayMicroseconds(2); 
    
  digitalWrite(SONAR_ERR_FWD_TRIGR, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(SONAR_ERR_FWD_TRIGR, LOW);
  float duration = pulseIn(SONAR_ERR_FWD_ECHO, HIGH, 30 * 1000);
  
  //Calculate the distance (in cm) based on the speed of sound.
  float distance = duration/58.2;
  
  return distance;
}

float chck_err_bck()
{
  digitalWrite(SONAR_ERR_BCK_TRIGR, LOW); 
  delayMicroseconds(2); 
    
  digitalWrite(SONAR_ERR_BCK_TRIGR, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(SONAR_ERR_BCK_TRIGR, LOW);
  float duration = pulseIn(SONAR_ERR_BCK_ECHO, HIGH, 30 * 1000);
  
  //Calculate the distance (in cm) based on the speed of sound.
  float distance = duration/58.2;
  
  return distance;
}


void motor(byte motor, float speed)
{
	Serial.print("V motor ");
	Serial.print(motor);
	Serial.print(": ");
	Serial.println(speed);

	byte pwm = abs(speed) * 255;

	if (pwm > 1)
	{
		if (speed > 0) 
		{
			motor_drive_fwd(motor, pwm);
		} 
		else
		{
			motor_drive_bwd(motor, pwm);
		}
	}
	else
	{
		motor_off(motor);
	}
}

void motor_off(byte motor)
{
	if (motor == M_L)
	{
		analogWrite(M_PWM_L, 0);
		digitalWrite(M_L1, LOW);
		digitalWrite(M_L2, LOW);
	}
	else
	{
		analogWrite(M_PWM_R, 0);
		digitalWrite(M_R1, LOW);
		digitalWrite(M_R2, LOW);	
	}
}

void motor_drive_fwd(byte motor, byte pwm)
{
	if (motor == M_L)
	{
		analogWrite(M_PWM_L, pwm);
		digitalWrite(M_L1, LOW);
		digitalWrite(M_L2, HIGH);
	}
	else
	{
		analogWrite(M_PWM_R, pwm);
		digitalWrite(M_R1, LOW);
		digitalWrite(M_R2, HIGH);	
	}
}

void motor_drive_bwd(byte motor, byte pwm)
{
	if (motor == M_L)
	{
		analogWrite(M_PWM_L, pwm);
		digitalWrite(M_L1, HIGH);
		digitalWrite(M_L2, LOW);
	}
	else
	{
		analogWrite(M_PWM_R, pwm);
		digitalWrite(M_R1, HIGH);
		digitalWrite(M_R2, LOW);	
	}
}
