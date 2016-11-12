#include <Servo.h> //F�r servo-motor funktioner
/*
Projekt fr�n
https://www.arduino.cc/en/Tutorial/Knob

Potentiometer: b10k (10kOhm)
	ben 1: gnd
	ben 2: l�sning
	ben 3: 5v
L�ses fr�n pinne med analogRead() varierar fr�n 0-1023

Samband mellan 0-180 & 0-1023:
	1023/180 ~~ 5,68

Servo: SG90 9g Micro Servo. Kan rotera 180grader, ~90 �t varje h�ll
	
*/
Servo servo;	//Skapar servo-object -- likt button-object i button.h
byte potPin = 0; //Pinne f�r potentiometer (ben2)
byte servoPin = 9;
float divider = 5.68;
int grad = 0;


void setup() {
	pinMode(11, OUTPUT); //Str�mmatning till servo
	servo.attach(servoPin); //V�ljer att servo ska s�ttas till 'servoPin'
	Serial.begin(9600);
}

void loop(){
	digitalWrite(13, 1);
	grad = analogRead(potPin) / divider;
	servo.write(grad);
	//servo.write(0);
	Serial.print("Pot:" );
	Serial.println(analogRead(potPin));
	delay(20);
}