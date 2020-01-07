#include <Wire.h>
#include <PRIZM.h>
#include <EasyTransferI2C.h>

#define SLAVE_ADDR 5
#define DEADBAND 10


typedef struct inputs{
	int16_t ly;
	int16_t lx;
	int16_t ry;
	int16_t rx;
}inputs;

int lx_mid, ly_mid, rx_mid, ry_mid = 0;

volatile inputs input;
EasyTransferI2C ET;
PRIZM prizm;
void setup() {
	Serial.begin(9600);

	prizm.PrizmBegin();
  //prizm.setMotorInvert(2,1);
	prizm.setMotorInvert(1,1);

	Wire.begin(SLAVE_ADDR);
	ET.begin(details(input), &Wire);
	Wire.onReceive(receiveEvent);
}
        


void loop() {
	if(ET.receiveData()){
    input.ly = processData(input.ly, 1);
    input.lx = processData(input.lx, 1);
    input.ry = processData(input.ry, 0);
    input.rx = processData(input.rx, 0);

		prizm.setMotorPowers((input.ly+input.lx), (input.ly-input.lx));
  	prizm.setServoPosition(1, input.ry);
  	prizm.setServoPosition(2, input.rx);
    //printData(&input);		
	}
}

void receiveEvent(int size){}

uint16_t processData(uint16_t x, bool isMotor){
    uint16_t y;
    y = constrain(x, 1000, 2000);
    if(isMotor){
      y = map(y, 1000, 2000, 100, -100);
      y = deadband(y, 0, DEADBAND);
    }else{
      y = map(y, 1000, 2000, 180, 0);
      y = deadband(y, 90, DEADBAND);      
      }
    return y;    
  }

void printData(inputs *input){
    Serial.print("ly: ");
    Serial.print(input->ly);
    Serial.print(" lx: ");
    Serial.print(input->lx);
    Serial.print(" ry: ");
    Serial.print(input->ry);
    Serial.print(" rx: ");
    Serial.println(input->rx);
    Serial.println("-------------");
  }
  
int deadband(int data, int midpoint, int range){
  if(data > midpoint && data < midpoint + range)
    return midpoint;
  else if(data < midpoint && data > midpoint - range)
    return midpoint;
  else
    return data;
}
