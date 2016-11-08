#include <Servo.h> //För servo-motor funktioner

/*
Projekt från
https://www.arduino.cc/en/Tutorial/Knob


Potentiometer: b10k (10kOhm)
	ben 1: gnd
	ben 2: läsning
	ben 3: 5v
Läses från pinne med analogRead() varierar från 0-1023

Samband mellan 0-180 & 0-1023:
	1023/180 ~~ 5,68

Servo: SG90 9g Micro Servo. Kan rotera 180grader, ~90 åt varje håll
	
*/


Servo servo;	//Skapar servo-object -- likt button-object i button.h
byte potPin = 0; //Pinne för potentiometer
byte servoPin = 9;
float divider = 5.68;
int grad = 0;


void setup() {
	pinMode(11, OUTPUT); //Strömmatning till servo
	servo.attach(servoPin); //Väljer att servo ska sättas till 'servoPin'
	Serial.begin(9600);

}

void loop() {
	digitalWrite(13, 1);
	grad = analogRead(potPin) / divider;
	servo.write(grad);
	//servo.write(0);
	Serial.println("Pot:" );
	Serial.println(analogRead(potPin));
	delay(10);
}