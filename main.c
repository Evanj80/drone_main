#include <Arduino.h>

  // Just trying to get simple throttle on the drone working combining both the transmission and motor test sketches
  
  double recieveTran;
  int trMotorPin = 10;
  int tlMotorPin = 9;
  int brMotorPin = 11;
  int blMotorPin = 3;
  int channell,channel2,channel3,channel4,channel5,channel6,channel7,channel8;
  int throttle;
void setup() {
  pinMode(trMotorPin, OUTPUT);
  pinMode(tlMotorPin, OUTPUT);
  pinMode(brMotorPin, OUTPUT);
  pinMode(blMotorPin, OUTPUT);
  pinMode(4,INPUT);
  Serial.begin(9600);
}

void loop() {
  
  channelCalc();
  //Saftey Lock on controller for User
    while(channel6 > 1000)
{
   channelCalc();
 analogWrite(trMotorPin,calcFR());
 analogWrite(brMotorPin,calcBR());
 analogWrite(tlMotorPin,calcFL());
 analogWrite(blMotorPin,calcBL());
  }


}

void channelCalc()
{
if(pulseIn(4,HIGH) > 4000)
{
  channell = pulseIn(4,HIGH);
  channel2 = pulseIn(4,HIGH);
  channel3 = pulseIn(4,HIGH);
  channel4 = pulseIn(4,HIGH);
  channel5 = pulseIn(4,HIGH);
  channel6 = pulseIn(4,HIGH);
  channel7 = pulseIn(4,HIGH);
  channel8 = pulseIn(4,HIGH);
}
//Serial.print("CH");
 //Serial.print(" ");
 //Serial.print(channel3);
//  Serial.println();
}

int getChannel1()
{
  return channell;
}

int getChannel2()
{
  return channel2;
}

int getChannel3()
{
  return channel3;
}

int getChannel4()
{
  return channel4;
}

int getChannel5()
{
  return channel5;
}

int getChannel6()
{
  return channel6;
}

int getChannel7()
{
  return channel7;
}

int getChannel8()
{
  return channel8;
}
int calcFR()
{
  return calcThrottle() + calcRightRoll()+ calcBackPitch();;
}
int calcFL()
{
    return calcThrottle() + calcLeftRoll()+ calcBackPitch();

}
int calcBL()
{
    return calcThrottle() + calcLeftRoll()+ calcFrontPitch();

}
int calcBR()
{
    return calcThrottle() + calcRightRoll() + calcFrontPitch();

}

// Calculating Right motion of drone, Cannot add power unless user is throttling drone
int calcRightRoll()
{
  if(calcThrottle != 128)
  {
  int roll = getChannel1();
  if(roll >1070 && roll<=1080)
  {
    return 0;
  }
  int add = roll/60;
 
  if(roll<1070)
  {
    return add;
  }
  return 0;
}
}
// Calculating left motion of drone, Cannot add power unless user is throttling drone

int calcLeftRoll()
{
   if(calcThrottle != 128)
   {
  int roll = getChannel1();
  if(roll >1070 && roll<=1080)
  {
    return 0;
  }
  int add = roll/60;
  if(roll>1080)
  {
    return add;
  }
  if(roll<1070)
  {
    return 0;
  }
}
}
// Essential function to get baseline power for motors
int calcThrottle()
{
  int temp = getChannel3();
  if(temp<650)
  {
    return 128;
  }
  int add = temp/26;
  temp = 128 + add;
  Serial.print(temp);
  Serial.println();
  return temp;
}
// Calculating front motion of drone, Cannot add power unless user is throttling drone

int calcFrontPitch()
{
   if(calcThrottle != 128)
   {
  int pitch = getChannel2();
 if(pitch >1070 && pitch <=1080)
  {
    return 0;
  }
  int pitchAdd=pitch/60;
  if(pitch>1080)
  {
    return pitchAdd;
  }
  return 0;
  
   } 
}
// Calculating backwards motion of drone, Cannot add power unless user is throttling drone

int calcBackPitch()
{
   if(calcThrottle != 128)
   {
 int pitch = getChannel2();
 if(pitch >1070 && pitch <=1080)
  {
    return 0;
  }
  int pitchAdd=pitch/60;
  if(pitch<1070)
  {
    return pitchAdd;
  }
  return 0;
}
}