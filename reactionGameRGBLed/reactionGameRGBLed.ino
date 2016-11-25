/*

*/

#include <Button.h>
#include <U8glib.h>

//Constants
#define pinLEDRed 9
#define pinLEDGreen 10
#define pinLEDBlue 11
#define ledBrightness 150

//Button objects for player buttons
Button player1Blue(2);
Button player1Green(3);
Button player1Red(4);
Button player2Blue(5);
Button player2Green(6);
Button player2Red(7);


bool player1set = 0;
bool player2set = 0;
bool letter1set = 0; 
bool letter3set = 0;
char player1name[3] = "AA";
char player2name[3] = "BB";
char letter1 = 'A';
char letter2 = 'A';
char letter3 = 'A';
char letter4 = 'A';
byte scorePlayer1 = 0;
byte scorePlayer2 = 0;


//OLED object
U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NONE);

//Function declarations
void ledOff(void);
void ledOn(byte PinNo);
void ledBlink(byte PinNo);
void drawDisplay(int mode);
void setName(void);
void genNames(void);
void changeLetterP1(bool upDown);
void changeLetterP2(bool upDown);

void setup(){
	Serial.begin(9600);
	player1Blue.begin();
	player1Green.begin();
	player1Red.begin();
	player2Blue.begin();
	player2Green.begin();
	player2Red.begin();
	pinMode(pinLEDRed, OUTPUT);
	pinMode(pinLEDGreen, OUTPUT);
	pinMode(pinLEDBlue, OUTPUT);
	ledOff();
}

void loop(){
	if(!player1set){
		setName();
		}
	
	display.firstPage();
	do{
		drawDisplay(1);
	}while(display.nextPage()); 
}

//Turns off LED
void ledOff(void){
	analogWrite(pinLEDBlue, 0);
	analogWrite(pinLEDRed, 0);
	analogWrite(pinLEDGreen, 0);
}

//Turns on LED
void ledOn(byte PinNo){
	ledOff();
	delay(10);
	analogWrite(PinNo, ledBrightness);
}

void ledBlink(byte PinNo){
	for(int i = 0;i<5;i++){
		ledOff();
		delay(200);
		ledOn(PinNo);
		delay(200);
	}
	ledOff();
}

void changeLetterP1(bool upDown){
	if(upDown)
		if(!letter1set){letter1++;}
		else{letter2++;}
	else
		if(!letter1set){letter1--;}
		else{letter2--;}
}

void changeLetterP2(bool upDown){
	if(upDown)
		if(!letter3set){letter3++;}
		else{letter4++;}
	else
		if(!letter3set){letter3--;}
		else{letter4--;}
}

//Allows players to set names (initials)
void setName(void){
	while(1){
		display.firstPage();
		do{
			drawDisplay(2);
		}while(display.nextPage());

		if(player1Red.pressed())
			changeLetterP1(1);
		if(player2Red.pressed())
			changeLetterP2(1);
		if(player1Blue.pressed())
			changeLetterP1(0);
		if(player2Blue.pressed())
			changeLetterP2(0);
		
		if(player1Green.pressed()){
			if(letter1set)
				player1set = 1;
			letter1set = 1;
		}

		if(player2Green.pressed()){
			if(letter3set)
				player2set = 1;
			letter3set = 1;
		}
		if(player2set && player1set){
			ledBlink(pinLEDGreen);
			return; //exits function -- no need to break while-loop
			}
	}
}

//Display output
void drawDisplay(int mode){
	switch(mode){
		case 1:
			genNames();
			display.drawLine(64,0,64,64);
			display.setFont(u8g_font_helvB12);
			display.drawStr(0,20, player1name);
			display.drawStr(100,20, player2name);
			break;
		case 2:
			genNames();
			display.drawLine(64,0,64,64);
			display.setFont(u8g_font_helvB10);
			display.drawStr(0,20, "P1 Name");
			display.drawStr(0,40, player1name);
			display.drawStr(66,20, "P2 Name");
			display.drawStr(66,40, player2name);
			break;
	}
}

//Prints player initials to name strings.
void genNames(void){
	sprintf(player1name, "%c%c", letter1, letter2);
	sprintf(player2name, "%c%c", letter3, letter4);
}