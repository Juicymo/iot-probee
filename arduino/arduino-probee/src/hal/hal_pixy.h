// Private
Pixy _pixy;

#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

#define RC_X_MIN        (PIXY_RCS_MIN_POS+300L) // Right
#define RC_X_MAX        (PIXY_RCS_MAX_POS-200L) // Left

#define RC_Y_MIN        (PIXY_RCS_MIN_POS+500L) // Up
#define RC_Y_MAX        (PIXY_RCS_MAX_POS-100L) // Down

class ServoLoop {
public:
  ServoLoop(int32_t pgain, int32_t dgain, int32_t min, int32_t max);

  void update(int32_t error);

  int32_t m_pos;
  int32_t m_pos_min;
  int32_t m_pos_max;
  int32_t m_prevError;
  int32_t m_pgain;
  int32_t m_dgain;
};

// ServoLoop panLoop(300, 500);
// ServoLoop tiltLoop(500, 700);
ServoLoop panLoop(300, 500, RC_X_MIN, RC_X_MAX);
ServoLoop tiltLoop(500, 700, RC_Y_MIN, RC_Y_MAX);

ServoLoop::ServoLoop(int32_t pgain, int32_t dgain, int32_t min, int32_t max) {
  m_pos = PIXY_RCS_CENTER_POS;
  m_pos_min = min;
  m_pos_max = max;
  m_pgain = pgain;
  m_dgain = dgain;
  m_prevError = 0x80000000L;
}

void ServoLoop::update(int32_t error) {
  long int vel;
  char buf[32];
  if (m_prevError!=0x80000000) {
    vel = (error*m_pgain + (error - m_prevError)*m_dgain)>>10;
    //sprintf(buf, "%ld\n", vel);
    //Serial.print(buf);
    m_pos += vel;
    if (m_pos>m_pos_max)
      m_pos = m_pos_max;
    else if (m_pos<m_pos_min)
      m_pos = m_pos_min;
  }
  m_prevError = error;
}

void _hal_pixy_print_blocks() {
  static int i = 0;
  static int k = 0;
  int j;
  uint16_t blocks;
  char buf[32];
  int32_t panError, tiltError;

  blocks = _pixy.getBlocks();

  if (blocks) {
    panError = X_CENTER-_pixy.blocks[0].x;
    tiltError = _pixy.blocks[0].y-Y_CENTER;

    panLoop.update(panError);
    tiltLoop.update(tiltError);

    //_pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);

    i++;

    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i % 50 == 0) {
      //TRACELN(panLoop.m_pos);
      //TRACELN(tiltLoop.m_pos);

      // int x = map(panLoop.m_pos, RC_X_MIN-10, RC_X_MAX+10, 0, 255);
      //
      // TRACE("X: ");
      // TRACE(panLoop.m_pos);
      // TRACE(", Y: ");
      // TRACE(tiltLoop.m_pos);
      // TRACELN();
      // TRACE("X: ");
      // TRACE(x);
      // TRACELN();

      if (!hal_laser_is_on(LASER_TURRET)) {
        //TRACELN("ON");
        hal_laser_on(LASER_TURRET);
      }

      sprintf(buf, "Detected %d:\n", blocks);
      TRACE(buf);
      for (j=0; j<blocks; j++) {
        sprintf(buf, "  block %d: ", j);
        TRACE(buf);
        _pixy.blocks[j].print();
      }
    }
  } else {
    if (hal_laser_is_on(LASER_TURRET)) {
      k++;

      if (k % 5000 == 0) { // only once per sec
        //TRACELN("OFF");
        hal_laser_off(LASER_TURRET);
      }
    }
  }
}

// Public
void setup_hal_pixy() {
	_pixy.init();
}

void hal_pixy_loop() {
  _hal_pixy_print_blocks();
}
