#include "Teleop.h"

Teleop::Teleop(PRIZM prizm, int deadband, byte channel1, byte channel2, byte channel3, byte channel4){
  _prizm = &prizm;
  _deadband = deadband;
  c1 = channel1;
  c2 = channel2;
  c3 = channel3;
  c4 = channel4;
  pinMode(c1, INPUT);
  pinMode(c2, INPUT);
  pinMode(c3, INPUT);
  pinMode(c4, INPUT);
  resetData(); 
}

void Teleop::drive(){
  readData();
  calc_speeds();
  _prizm->setMotorPowers(speeds.left_motor, speeds.right_motor);
  _prizm->setServoPosition(c3, speeds.servo1);
  _prizm->setServoPosition(c4, speeds.servo2);
}

void Teleop::calc_speeds(){
  //servo position    0-180
  //motor speed    -100-100

  speeds.servo1 = deadband(map(input.c3, 0,1023, 0,180), 90, _deadband);
  speeds.servo2 = deadband(map(input.c4, 0,1023, 0,180), 90, _deadband);
  int x = map(input.c1, 0, 1023, -100,100);
  int y = map(input.c2, 0, 1023, -100,100);
  //invert a motor?
  //left =  (ly+rx)/2
  //right = (ly-rx)/2
  speeds.left_motor = deadband((y + x)/2, 0, _deadband);
  speeds.right_motor = deadband((y + x)/2, 0, _deadband);
}

void Teleop::resetData(){
  input.c1 = 0; 
  input.c2 = 0; 
  input.c3 = 0; 
  input.c4 = 0; 
}

void Teleop::readData(){
  input.c1 = pulseIn(c1, HIGH);
  input.c2 = pulseIn(c2, HIGH);
  input.c3 = pulseIn(c3, HIGH);
  input.c4 = pulseIn(c4, HIGH);
}

int Teleop::deadband(int data, int midpoint, int range){
  if(data > midpoint && data < midpoint + range)
    return midpoint;
  else if(data < midpoint && data > midpoint - range)
    return midpoint;
  else
    return data;
}
