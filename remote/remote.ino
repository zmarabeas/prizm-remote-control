#include <PRIZM.h>

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

#define DEADBAND 5


//structure to hold incoming rc data
struct inputs_t{
  uint8_t c1;
  uint8_t c2;
  uint8_t c3;
  uint8_t c4;
}inputs_t;

//structure to hold motor speeds
struct speeds_t{
  int left_motor;
  int right_motor;
  int servo1;
  int servo2;
}speeds_t;

void readData(inputs_t*);
void calc_speeds(inputs_t*, speeds_t*);
void resetData(inputs_t*);
void drive(speeds_t*)
int deadband(int, int, int);

struct speeds_t* speeds;
struct inputs_t* inputs;

PRIZM prizm;

void setup(){
  Serial.begin(9600);
  pinMode(CHANNEL4, INPUT);
  pinMode(CHANNEL3, INPUT);
  pinMode(CHANNEL2, INPUT);
  pinMode(CHANNEL1, INPUT);
}

void loop(){
  readData(inputs);
  calc_speeds(inputs, speeds);
  prizm.setMotorPowers(speeds.left_motor, speeds.right_motor);
  prizm.setServoPosition(c3, speeds.servo1);
  prizm.setServoPosition(c4, speeds.servo2);
}

void calc_speeds(inputs_t* inputs, speeds_t* speeds){
  //servo position    0-180
  //motor speed    -100-100

  speeds->servo1 = deadband(map(inputs->c3, 0,1023, 0,180), 90, DEADBAND);
  speeds->servo2 = deadband(map(inputs->c4, 0,1023, 0,180), 90, DEADBAND);
  int x = map(inputs->c1, 0, 1023, -100,100);
  int y = map(inputs->c2, 0, 1023, -100,100);
  //invert a motor?
  //left =  (ly+rx)/2
  //right = (ly-rx)/2
  speeds->left_motor = deadband((y + x)/2, 0, DEADBAND);
  speeds->right_motor = deadband((y + x)/2, 0, DEADBAND);
}

void readData(inputs_t* inputs){
  inputs->c1 = pulseIn(c1, HIGH);
  inputs->c2 = pulseIn(c2, HIGH);
  inputs->c3 = pulseIn(c3, HIGH);
  inputs->c4 = pulseIn(c4, HIGH);
}

void resetData(inputs_t* inputs){
  inputs->c1 = 0; 
  inputs->c2 = 0; 
  inputs->c3 = 0; 
  inputs->c4 = 0; 
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
