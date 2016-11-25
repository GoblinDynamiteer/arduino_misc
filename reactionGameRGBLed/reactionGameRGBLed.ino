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


const byte nameSet = 0;
char player1name[3] = "AA";
char player2name[3] = "BB";
char letter1 = 'A';
char letter2 = 'A';
char letter3 = 'A';
char letter4 = 'A';

//OLED object
U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NONE);

//Function declarations
void ledOff(void);
void ledOn(byte PinNo);
void drawDisplay(int mode);
void setName(void);

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
	while(!nameSet){
		setName();
		}
	display.firstPage();
	do{
		drawDisplay(1);
	}while(display.nextPage()); 
}

void ledOff(void){
	analogWrite(pinLEDBlue, 0);
	analogWrite(pinLEDRed, 0);
	analogWrite(pinLEDGreen, 0);
}

void ledOn(byte PinNo){
	ledOff();
	delay(10);
	analogWrite(PinNo, ledBrightness);
}

void setName(void){
	display.firstPage();
	do{
		drawDisplay(2);
	}while(display.nextPage());
}

void drawDisplay(int mode){
	switch(mode){
		case 1:
			display.drawLine(64,0,64,64);
			display.setFont(u8g_font_helvB12);
			display.drawStr(0,20, player1name);
			display.drawStr(100,20, player2name);
			break;
		case 2:
			sprintf(player1name, "%c%c", letter1, letter2);
			sprintf(player2name, "%c%c", letter3, letter4);
			display.drawLine(64,0,64,64);
			display.setFont(u8g_font_helvB10);
			display.drawStr(0,20, "P1 Name");
			display.drawStr(0,40, player1name);
			display.drawStr(65,20, "P2 Name");
			display.drawStr(65,40, player2name);
			break;
		}
}