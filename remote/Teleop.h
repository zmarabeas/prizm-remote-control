#ifndef Teleop_h
#define Teleop_h

#include <PRIZM.h>

class Teleop{
  //structure to hold incoming rc data
  typedef struct inputs{
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;
    uint8_t c4;
  }inputs;

  //structure to hold motor speeds
  typedef struct drive_speeds{
    int left_motor;
    int right_motor;
    int servo1;
    int servo2;
  }drive_speeds;

  public:
    //prizm object, channel pins
    Teleop(PRIZM, int, byte, byte, byte, byte);
    void drive();

  private:
    void resetData();
    void readData();
    void calc_speeds();
    int deadband(int, int, int);
    PRIZM* _prizm; 
    int _deadband;
    byte c1;
    byte c2;
    byte c3;
    byte c4;
    inputs input;
    drive_speeds speeds;
};
#endif
