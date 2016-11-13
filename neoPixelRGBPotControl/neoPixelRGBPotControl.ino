//Styr RGB-värden för LED-ring med 3 potentiometrar, skriv ut värden på OLED-Display.

#include <Adafruit_NeoPixel.h>
#include <U8glib.h>

const byte neoPin = 10;
const byte neoPixels = 24;
byte neoBright = 90, red, green, blue;
//Pins för potentiometrar för att sätta RGB
const byte potRed = A0, potGreen = A1, potBlue = A2;

//Deklaration av funktion
void drawDisplay();

//Objekt
Adafruit_NeoPixel ledRing = Adafruit_NeoPixel(neoPixels, neoPin, NEO_GRB);
U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);


void setup(){
	ledRing.begin();
	ledRing.setBrightness(neoBright);
	ledRing.show();
	pinMode(potRed, INPUT);
	pinMode(potGreen, INPUT);
	pinMode(potBlue, INPUT);
}

void loop(){
	//Tänder LEDs
	for(int i=0; i<neoPixels;i++){
		ledRing.setPixelColor(i, ledRing.Color(red,green,blue));
		ledRing.show();
	}
	delay(500);

	//skriver ut RBG-värden på display
	oled.firstPage(); 
	do{
		drawDisplay();
	}while(oled.nextPage()); 

	//Mappar potentiometer-värden till R/G/B
	red = map(analogRead(potRed), 0, 1023, 0, 255);
	green = map(analogRead(potGreen), 0, 1023, 0, 255);
	blue = map(analogRead(potBlue), 0, 1023, 0, 255);
	delay(50);
}


void drawDisplay(){
	char rgbString[15];
	sprintf(rgbString, "R%03d G%03d B%03d", red, green, blue);
	//Sätter teckensnitt Helvetica 10
	oled.setFont(u8g_font_helvB10);
	oled.drawStr(0,15, rgbString);
}