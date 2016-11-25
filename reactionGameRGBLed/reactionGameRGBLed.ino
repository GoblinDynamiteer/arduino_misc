/*

*/

#include <Button.h>


Button player1Blue(2);
Button player1Green(3);
Button player1Red(4);
Button player2Blue(5);
Button player2Green(6);
Button player2Red(7);

void setup(){
	Serial.begin(9600);
	player1Blue.begin();
	player1Green.begin();
	player1Red.begin();
	player2Blue.begin();
	player2Green.begin();
	player2Red.begin();
}

void loop(){
	if(player1Red.pressed()){
		Serial.println("P1 RED");
	}
	else if(player1Blue.pressed()){
		Serial.println("P1 BLUE");
	}
	else if(player1Green.pressed()){
		Serial.println("P1 GREEN");
	}
	else if(player2Blue.pressed()){
		Serial.println("P2 BLUE");
	}
	else if(player2Green.pressed()){
		Serial.println("P2 GREEN");
	}
	else if(player2Red.pressed()){
		Serial.println("P2 RED");
	}
}