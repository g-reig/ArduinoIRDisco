#include <IRremote.hpp>

bool play = false;
bool RGBvalues[3] = {false,false,false};

bool disco = false;
int IRPin = 2;
int redPin = 3;
int greenPin = 4;
int bluePin = 5; 
int buzzerPin = 9;
void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(IRPin, ENABLE_LED_FEEDBACK); 
  Serial.begin(9600);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
}

void song(int buzzer) {
  tone(buzzer, 1046); 
  delay(250);
  tone(buzzer, 1244); 
  delay(250); 
  tone(buzzer, 1400); 
  delay(250); 
  tone(buzzer, 1510); 
  delay(250);
  tone(buzzer, 1400); 
  delay(250);
  tone(buzzer, 1244); 
  delay(250); 
  tone(buzzer, 1046); 
  delay(250); 
  noTone(buzzer); 
  delay(500); 
  tone(buzzer, 932); 
  delay(125);
  tone(buzzer, 1174); 
  delay(125); 
  tone(buzzer, 1046); 
  delay(250);
  // end of first
  noTone(buzzer); 
  delay(500); 
  tone(buzzer, 780); 
  delay(250); 
  tone(buzzer, 525); 
  delay(250); 
  noTone(buzzer); 
  delay(250);
  //secont part
  tone(buzzer, 1046); 
  delay(250);
  tone(buzzer, 1244); 
  delay(250); 
  tone(buzzer, 1400); 
  delay(250); 
  tone(buzzer, 1510); 
  delay(250);
  tone(buzzer, 1400); 
  delay(250);
  tone(buzzer, 1244); 
  delay(250);
  tone(buzzer, 1400); 
  delay(250);
  noTone(buzzer); 
  delay(750);
  //fast part
  tone(buzzer, 1510); 
  delay(125);
  tone(buzzer, 1400); 
  delay(125);
  tone(buzzer, 1244); 
  delay(125);
  tone(buzzer, 1510); 
  delay(125);
  tone(buzzer, 1400); 
  delay(125);
  tone(buzzer, 1244); 
  delay(125);
  tone(buzzer, 1510); 
  delay(125);
  tone(buzzer, 1400); 
  delay(125);
  tone(buzzer, 1244); 
  delay(125);
  tone(buzzer, 1510); 
  delay(125);
  tone(buzzer, 1400); 
  delay(125);
  tone(buzzer, 1244); 
  delay(125);
  tone(buzzer, 1510); 
  delay(125);
  noTone(buzzer); 
  return;
}

void rgbColor() {
  Serial.println(RGBvalues[0]);
  digitalWrite(redPin,RGBvalues[0]);
  digitalWrite(greenPin,RGBvalues[1]);
  digitalWrite(bluePin,RGBvalues[2]);
}

void loop() {
  rgbColor();
  if (play) {
    song(buzzerPin);
    play = false;
  }
  
  if (disco) {
    for (int i = 0; i < 3; ++i) {
      RGBvalues[i] = !RGBvalues[i];
    }
    rgbColor();
    delay(100);
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