#include <Wire.h>
#include <EasyTransferI2C.h>

#define SLAVE_ADDR 5
#define CHANNEL1 3
#define CHANNEL2 5
#define CHANNEL3 4
#define CHANNEL4 2

#define DEADBAND 5


typedef struct inputs{
	int16_t ly;
	int16_t lx;
	int16_t ry;
	int16_t rx;
}inputs;

volatile inputs input;
EasyTransferI2C ET;
void setup() {
	Serial.begin(9600);
	Wire.begin();
	ET.begin(details(input), &Wire);
	input.ly = 0;
	input.lx = 0;
	input.ry = 0;
	input.rx = 0;
}

void loop() {
	input.ly = pulseIn(CHANNEL1, HIGH);
	input.lx = pulseIn(CHANNEL2, HIGH);
	input.ry = pulseIn(CHANNEL3, HIGH);
	input.rx = pulseIn(CHANNEL4, HIGH);

	/*
	Serial.print("ly: ");
	Serial.print(input.ly);
	Serial.print(" lx: ");
	Serial.print(input.lx);
	Serial.print(" ry: ");
	Serial.print(input.ry);
	Serial.print(" rx: ");
	Serial.println(input.rx);
*/

	ET.sendData(SLAVE_ADDR);
	//delay(5000);
}
int deadband(int data, int midpoint, int range){
  if(data > midpoint && data < midpoint + range)
    return midpoint;
  else if(data < midpoint && data > midpoint - range)
    return midpoint;
  else
    return data;
}
