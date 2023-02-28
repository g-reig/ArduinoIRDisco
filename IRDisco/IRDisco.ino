#include <IRremote.hpp>

bool play = false;
bool RGBvalues[3] = {false,false,false};

bool disco = false;
int IRPin = 2;
int redPin = 3;
int greenPin = 4;
int bluePin = 5; 
int buzzerPin = 9;

unsigned int partitureIndex = 0;
const int songLength = 74;
unsigned int partiture[songLength] = {1046,250,1244,250,1400,250,1510,250,1400,250,1244,250,1046,250,0,500,932,125,1174,125,1046,250,0,500,780,250,525,250,0,250,1046,250,1244,250,1400,250,1510,250,1400,250,1244,250,1400,250,0,750,1510,125,1400,125,1244,125,1510,125,1400,125,1244,125,1510,125,1400,125,1244,125,1510,125,1400,125,1244,125,1510,125,0,0};

unsigned long previousMillis = 0;
unsigned long previousMillisSong = 0;


void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(IRPin, ENABLE_LED_FEEDBACK); 
  Serial.begin(9600);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
}

void song(int currentMilis) {
  if (currentMilis - previousMillisSong >= partiture[partitureIndex+1]) {
    if (partiture[partitureIndex] != 0) tone(buzzerPin,partiture[partitureIndex]);
    else noTone(buzzerPin);
    partitureIndex += 2;
    previousMillisSong = currentMilis;
  }
  return;
}

void rgbColor() {
  Serial.println(RGBvalues[0]);
  digitalWrite(redPin,RGBvalues[0]);
  digitalWrite(greenPin,RGBvalues[1]);
  digitalWrite(bluePin,RGBvalues[2]);
}

void loop() {
  unsigned long currentMillis = millis();
  rgbColor();
  if (play) {
    song(currentMillis);
    if (partitureIndex == songLength) play = false;
  }
  
  if (disco && currentMillis - previousMillis >= 90) {
    for (int i = 0; i < 3; ++i) {
      RGBvalues[i] = !RGBvalues[i];
    }
    rgbColor();
    previousMillis = currentMillis;
  }

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    auto command = IrReceiver.decodedIRData.decodedRawData;
    
    switch (command) {
      //1
      case 0xF30CFF00: 
        RGBvalues[0] = !RGBvalues[0];
        rgbColor();
        break;
      //2  
      case 0xE718FF00:
        RGBvalues[1] = !RGBvalues[1];
        rgbColor();
        break;
      //3
      case 0xA15EFF00:
        RGBvalues[2] = !RGBvalues[2];
        rgbColor();
        break;
      //EQ
      case 0xE619FF00:
        disco = !disco;
        break;
      //PLAY
      case 0xBF40FF00:
        play = true;
        break;
    }
  }
  IrReceiver.resume();
}