#include <IRremote.hpp>

bool play = false;
bool values[3] = {false,false,false};
bool disco = false;
void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(2, ENABLE_LED_FEEDBACK); 
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
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

void loop() {
  if (play) {
    song(9);
    play = false;
  }
  
  if (disco) {
    for (int i = 0; i < 3; ++i) {
      digitalWrite(3+i,values[i]);
      values[i] = !values[i];
    }
    delay(100);
  }
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    auto command = IrReceiver.decodedIRData.decodedRawData;
    
    switch (command) {
      //1
      case 0xF30CFF00: 
        digitalWrite(3,values[0]);
        if (values[0] == false) values[0] = true;
        else values[0] = false;
        break;
      //2  
      case 0xE718FF00:
        digitalWrite(4,values[1]);
        if (values[1] == false) values[1] = true;
        else values[1] = false;
        break;
      //3
      case 0xA15EFF00:
        digitalWrite(5,values[2]);
        if (values[2] == false) values[2] = true;
        else values[2] = false;
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
