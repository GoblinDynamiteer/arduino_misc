/* Kjell.com - Hur funkar Arduino?, Sida 210

Anslut till wifi-nätverk med WiFi-modul ESP8266
Sätt upp enkel webserver med sida

*/

#include <SoftwareSerial.h>
#include <WiFiEsp.h>

SoftwareSerial Serial1(6,7);


//SSID & lösenord för WiFi-modul
char ssid[] = "";
char pw[] = "";

int status = WL_IDLE_STATUS;

//Status för LED (använder pin 13 på kortet)
int ledStatus = LOW;

//Starta webserver (från WiFiEsp.h)
WiFiEspServer server(80);
RingBuffer buf(8);

void printWiFiStatus();

void setup(){
	pinMode(13, OUTPUT);
	//Serial för debug och info
	Serial1.begin(9600);
	Serial.begin(115200);
	
	WiFi.init(&Serial1);
	
	if(WiFi.status() == WL_NO_SHIELD){
		Serial.println("WiFi Shield not present!");
		while(1);
	}
	
	while(status != WL_CONNECTED){
		Serial.print("Connecting to SSID: ");
		Serial.println(ssid);
		
		status = WiFi.begin(ssid, pw);
	}
	
	Serial.println("Connection successful!");
	printWiFiStatus();
	
	//startar webserver
	server.begin();
}

//code from https://github.com/bportaluri/WiFiEsp/blob/master/examples/WebServerLed/WebServerLed.ino
//Somewhat edited
void loop()
{
  WiFiEspClient client = server.available();  // listen for incoming clients

  if (client) {                               // if you get a client,
    Serial.println("New client");             // print a message out the serial port
    buf.init();                               // initialize the circular buffer
    while (client.connected()) {              // loop while the client's connected
      if (client.available()) {               // if there's bytes to read from the client,
        char c = client.read();               // read a byte, then
        buf.push(c);                          // push it to the ring buffer

        // printing the stream to the serial monitor will slow down
        // the receiving of data from the ESP filling the serial buffer
        //Serial.write(c);
        
        // you got two newline characters in a row
        // that's the end of the HTTP request, so send a response
        if (buf.endsWith("\r\n\r\n")) {
          sendHttpResponse(client);
          break;
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (buf.endsWith("GET /H")) {
          Serial.println("Turn led ON");
          ledStatus = HIGH;
          digitalWrite(13, HIGH);
        }
        else if (buf.endsWith("GET /L")) {
          Serial.println("Turn led OFF");
          ledStatus = LOW;
          digitalWrite(13, LOW);
        }
      }
    }
    
    // close the connection
    client.stop();
    Serial.println("Client disconnected");
	delay(10);
  }
}

void sendHttpResponse(WiFiEspClient client)
{
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  
  // the content of the HTTP response follows the header:
  client.print("The LED is ");
  client.print(ledStatus);
  client.println("<br>");
  client.println("<br>");
  
  client.println("Click <a href=\"/H\">here</a> turn the LED on<br>");
  client.println("Click <a href=\"/L\">here</a> turn the LED off<br>");
  
  // The HTTP response ends with another blank line:
  client.println();
}

void printWiFiStatus(){
		Serial.print("SSID: ");
		Serial.println(WiFi.SSID());
		IPAddress ip = WiFi.localIP();
		Serial.print("Local IP: ");
		Serial.println(ip);
}