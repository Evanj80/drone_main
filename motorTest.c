
//Intial Motor Control testing.
//
#include <Arduino.h>


  int trMotorPin = 10;
  int tlMotorPin = 9;
  int brMotorPin = 11;
  int blMotorPin = 3;
void setup() {
  pinMode(trMotorPin, OUTPUT);
  pinMode(tlMotorPin, OUTPUT);
  pinMode(brMotorPin, OUTPUT);
  pinMode(blMotorPin, OUTPUT);
  Serial.begin(9600);
  
  // put your setup code here, to run once:

}

void loop() {
 while (Serial.available() > 0) {
   int testNumber = Serial.read();
   
   if(testNumber == 1)//drone heads forward
   {
  analogWrite(trMotorPin,180);   
  delay(500);

  analogWrite(brMotorPin,170);
     delay(500);

  analogWrite(tlMotorPin,180);
     delay(500);

  analogWrite(blMotorPin,170);
   delay(500);

   }
   if(testNumber == 2)//Drone heads backwards
   {
 analogWrite(trMotorPin,170);
 analogWrite(brMotorPin,180);
 analogWrite(tlMotorPin,170);
 analogWrite(blMotorPin,180);
  delay(500);

   }
    if(testNumber == 3)//Drone heads right
    {
 analogWrite(trMotorPin,180);
 analogWrite(brMotorPin,180);
 analogWrite(tlMotorPin,170);
 analogWrite(blMotorPin,170);
 delay(500);
    }
    if(testNumber == 4)//Drone heads left
    {
 analogWrite(trMotorPin,170);
 analogWrite(brMotorPin,170);
 analogWrite(tlMotorPin,180);
 analogWrite(blMotorPin,180);
  delay(500);

    }
    
   if(testNumber == 5)//Drone falls from the sky
    {
 analogWrite(trMotorPin,128);
 analogWrite(brMotorPin,128);
 analogWrite(tlMotorPin,128);
 analogWrite(blMotorPin,128);
  delay(500);


 }
 if(testNumber == 6)
 {
   analogWrite(trMotorPin,170);
   delay(500);

 }
}
}
int calcTr()
{
 return 0;
}

int calcTl()
{
    return 0;
}

int calcBr()
{
  return 0;
}

int calcBl()
{
  return 0;
}