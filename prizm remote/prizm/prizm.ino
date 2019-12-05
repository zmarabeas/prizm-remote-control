#include <Wire.h>
#include <PRIZM.h>
#include <EasyTransferI2C.h>

#define SLAVE_ADDR 5
#define DEADBAND 5


typedef struct inputs{
	int16_t ly;
	int16_t lx;
	int16_t ry;
	int16_t rx;
}inputs;

volatile inputs input;
EasyTransferI2C ET;
PRIZM prizm;
void setup() {
	Serial.begin(9600);

	prizm.PrizmBegin();
	prizm.setMotorInvert(1,1);

	Wire.begin(SLAVE_ADDR);
	ET.begin(details(input), &Wire);
	Wire.onReceive(receiveEvent);
}

void loop() {
	if(ET.receiveData()){
		input.ly = constrain(input.ly, 900, 1500);
		input.ly = map(input.ly, 900, 1500, 100, -100);
		input.ly = deadband(input.ly, 0, DEADBAND);

		input.lx = map(input.lx, 1000, 2000, 100, -100);
		input.lx = deadband(input.lx, 0, DEADBAND);

		input.ry = map(input.ry, 1000, 2000, 180, 0);
		input.ry = deadband(input.ry, 90, DEADBAND);


		input.rx = constrain(input.rx, 900, 1500);
		input.rx = map(input.rx, 900, 1500, 180, 0);
		input.rx = deadband(input.rx, 90, DEADBAND);

		prizm.setMotorPowers((input.ly+input.lx), (input.ly-input.lx));
  		prizm.setServoPosition(1, input.ry);
  		prizm.setServoPosition(2, input.rx);
		Serial.print("ly: ");
		Serial.print(input.ly);
		Serial.print(" lx: ");
		Serial.print(input.lx);
		Serial.print(" ry: ");
		Serial.print(input.ry);
		Serial.print(" rx: ");
		Serial.println(input.rx);
		Serial.println("-------------");
	}
}

void receiveEvent(int size){}
int deadband(int data, int midpoint, int range){
  if(data > midpoint && data < midpoint + range)
    return midpoint;
  else if(data < midpoint && data > midpoint - range)
    return midpoint;
  else
    return data;
}
