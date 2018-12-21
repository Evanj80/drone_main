#include <Arduino.h>

  // Just trying to get simple throttle on the drone working combining both the transmission and motor test sketches

  double recieveTran;
  int trMotorPin = 10;
  int tlMotorPin = 9;
  int brMotorPin = 11;
  int blMotorPin = 8;
  int transmitter= 3;
  int baseLine = 30;
  int channell,channel2,channel3,channel4,channel5,channel6,channel7,channel8;
  int throttle;
  bool exm;
void setup() {
  //Establishing what each pin does on the Arduino
  pinMode(trMotorPin, OUTPUT);
  pinMode(tlMotorPin, OUTPUT);
  pinMode(brMotorPin, OUTPUT);
  pinMode(blMotorPin, OUTPUT);
  pinMode(3,INPUT);
  //At which freqwuency the board recieves and reads signals
  Serial.begin(9600);
  //Calibrating Motors for maximum power
  analogWrite(trMotorPin,255);
  analogWrite(brMotorPin,255);
  analogWrite(tlMotorPin,255);
  analogWrite(blMotorPin,255);
  delay(3000);
  //Calibrating for the lowest power settings
  analogWrite(trMotorPin,0);
  analogWrite(brMotorPin,0);
  analogWrite(tlMotorPin,0);
  analogWrite(blMotorPin,0);

}

void loop() {

  channelCalc();
  //Saftey Lock on controller for User
    while(channel6 > 1000)
{
  if(//Channel that controls expert mode is flipped)
  {
   exm = true
  }
  exm = false
   channelCalc();
 analogWrite(trMotorPin,calcFR(exm));
 analogWrite(brMotorPin,calcBR(exm));
 analogWrite(tlMotorPin,calcFL(exm));
 analogWrite(blMotorPin,calcBL(exm));
  }


}