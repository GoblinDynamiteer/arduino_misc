int led[4] = {5,6,9,10};
int brightness[4] = {0,30,60,90};
boolean ud[4] = {1,1,1,1};
int fadeAmount = 3;

void setup() {
  	for(int i=0;i<4;i++){
		pinMode(led[i], OUTPUT);
	 }
  Serial.begin(9600);
}

void loop() {
	for(int i=0;i<4;i++){
		analogWrite(led[i], brightness[i]);
		if(ud[i]){
			brightness[i] += fadeAmount;
			if(brightness[i] >= 90){
				ud[i] = 0;
			}
		}
		else{
			brightness[i] -= fadeAmount;
			if(brightness[i] <= 5){
				ud[i] = 1;
			}
		}
		Serial.print("LED ");
		Serial.print(led[i]);
		Serial.print(": ");
		Serial.println(brightness[i]);
	}
  delay(5);
}