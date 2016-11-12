
#include <Servo.h>

int lastServo = -1;
Servo servomotor;
void setServo(int deg);


void setup(){
	Serial.begin(9600);
	servomotor.attach(9);
	for(int i=0;i<=180;i+=30){
		setServo(i);
		delay(2000);
	}
}

void loop(){
	delay(2000);
	setServo(random(1,179));
}

void setServo(int deg){
	if(lastServo != deg){
		Serial.print("Servo: ");
		Serial.println(deg);
		servomotor.write(deg);
		lastServo = deg;
	}
}