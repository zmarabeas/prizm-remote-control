#include <PRIZM.h>


#define LY 3
#define LX 5
#define RY 4
#define RX 2

#define DEADBAND 8

PRIZM prizm;
int ly_mid, lx_mid, ry_mid, rx_mid;

void setup(){
  Serial.begin(9600);
  prizm.PrizmBegin();
  prizm.setMotorInvert(1,1);
  pinMode(LY, INPUT);
  pinMode(LX, INPUT);
  pinMode(RY, INPUT);
  pinMode(RX, INPUT);
  Serial.print("Calibrating");
  ly_mid = pulseIn(LY, HIGH);
  delay(500);
  Serial.print(".");
  lx_mid = pulseIn(LX, HIGH);
  delay(500);
  Serial.print(".");
  ry_mid = pulseIn(RY, HIGH);
  delay(500);
  Serial.print(".");
  rx_mid = pulseIn(RX, HIGH);
  delay(500);
  Serial.println(".");
  Serial.println("Complete");
  Serial.println("-------------------");
  Serial.print("ly midpoint: ");
  Serial.print(ly_mid);
  Serial.print(" lx midpoint: ");
  Serial.print(lx_mid);
  Serial.print(" ry midpoint: ");
  Serial.print(ry_mid);
  Serial.print(" rx midpoint: ");
  Serial.println(rx_mid);
  delay(5000);
}

void loop(){
  int ly = pulseIn(LY, HIGH);
  int lx = pulseIn(LX, HIGH);
  int ry = pulseIn(RY, HIGH);
  int rx = pulseIn(RX, HIGH);
  ly = constrain(ly, 900, 1500);
  ly = map(ly, 900, 1500, 100, -100);
  ly = deadband(ly, 0, DEADBAND);

  lx = map(lx, 1000, 2000, 100, -100);
  lx = deadband(lx, 0, DEADBAND);

  ry = map(ry, 1000, 2000, 180, 0);
  ry = deadband(ry, 90, DEADBAND);

  rx = constrain(rx, 900, 1500);
  rx = map(rx, 900, 1500, 180, 0);
  rx = deadband(rx, 90, DEADBAND);

  //left = (ly+rx)/2
  //right = (ly-rx)/2
  prizm.setMotorPowers((ly+lx)/2, (ly-lx)/2);
  prizm.setServoPosition(2, ry);
  prizm.setServoPosition(3, rx);

  Serial.print("LY: ");
  Serial.print(ly);
  Serial.print(" LX: ");
  Serial.print(lx);
  Serial.print(" RY: ");
  Serial.print(ry);
  Serial.print(" RX: ");
  Serial.println(rx);
}


int deadband(int data, int midpoint, int range){
  if(data > midpoint && data < midpoint + range)
    return midpoint;
  else if(data < midpoint && data > midpoint - range)
    return midpoint;
  else
    return data;
}






































/*
#include <PRIZM.h>
#include "Teleop.h"



TODO:
  1. servo mixing
  2. deadband
  3. invert motor
  4. move to sep. file
  5. refactor to class
  6. follow arduino api style


#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

//structure to hold incoming rc data
typedef struct inputs{
  uint8_t c1;
  uint8_t c2;
  uint8_t c3;
  uint8_t c4;
}inputs;

//structure to hold motor speeds
typedef struct drive_speeds{
  int8_t left_motor;
  int8_t right_motor;
  uint8_t servo1;
  uint8_t servo2;
}drive_speeds;

//function prototypes
void resetData(inputs *input);
void readData(inputs *input);
void calc_speeds(inputs *input, drive_speeds *speeds);
void drive(drive_speeds *speeds, PRIZM prizm);

//move to main file
inputs input = {0,0,0,0};
drive_speeds speeds = {0,0,0,0};
PRIZM prizm;

void setup() {
  Serial.begin(9600);
  prizm.PrizmBegin();

  //initialize radio pins
  pinMode(CHANNEL1, INPUT);
  pinMode(CHANNEL2, INPUT);
  pinMode(CHANNEL3, INPUT);
  pinMode(CHANNEL4, INPUT);
}

void loop() {
  resetData(&input); 
  readData(&input);
  calc_speeds(&input, &speeds);
  drive(&speeds, prizm);
}

//set prizm motor and servo speeds 
void drive(drive_speeds *speeds, PRIZM prizm){
  prizm.setMotorPowers(speeds->left_motor, speeds->right_motor);

}

//calculate the speeds of motors and servos based on rc input
void calc_speeds(inputs *input, drive_speeds *speeds){
  //channel 1 left stick y
  //channel 2 left stick x
  //channel 3 right stick y
  //channel 4 right stick x 
  
  //servo position    0-180
  //motor speed    -100-100

  speeds->servo1 = map(input->c3, 0,1023, 0,180);
  speeds->servo2 = map(input->c4, 0,1023, 0,180);

  int8_t x = map(input->c1, 0, 1023, -100,100);
  int8_t y = map(input->c2, 0, 1023, -100,100);
  //put deadband
  //invert a motor?
  //left =  (ly+rx)/2
  //right = (ly-rx)/2
  speeds->left_motor = (y + x)/2;
  speeds->right_motor = (y - x)/2;
}

//reset input data
void resetData(inputs *input){
  input->c1 = 0;
  input->c2 = 0;
  input->c3 = 0;
  input->c4 = 0;
}

//read incoming data
void readData(inputs *input){
  input->c1 = pulseIn(CHANNEL1, HIGH);
  input->c2 = pulseIn(CHANNEL2, HIGH);
  input->c3 = pulseIn(CHANNEL3, HIGH);
  input->c4 = pulseIn(CHANNEL4, HIGH);
}
*/
