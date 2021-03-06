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
  double multiplier;

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
  delay(4000);
  //Calibrating for the lowest power settings
  analogWrite(trMotorPin,0);
  analogWrite(brMotorPin,0);
  analogWrite(tlMotorPin,0);
  analogWrite(blMotorPin,0);
  delay(4000);

}

void loop() {

  channelCalc();
  //Saftey Lock on controller for User
    while(channel6 > 1000)
{
  //Controls how powerful and sensitive motors are
  if(//Channel that controls expert mode is flipped)
  {
   multiplier = 1.5;
  }
  multiplier = 1.0;
   channelCalc();
 analogWrite(trMotorPin,calcFR(sickoMode));
 analogWrite(brMotorPin,calcBR(sickoMode));
 analogWrite(tlMotorPin,calcFL(sickoMode));
 analogWrite(blMotorPin,calcBL(sickoMode));
  }


}