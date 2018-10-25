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
void setup() {
  pinMode(trMotorPin, OUTPUT);
  pinMode(tlMotorPin, OUTPUT);
  pinMode(brMotorPin, OUTPUT);
  pinMode(blMotorPin, OUTPUT);
  pinMode(3,INPUT);
  Serial.begin(9600);
  analogWrite(trMotorPin,255);
 analogWrite(brMotorPin,255);
 analogWrite(tlMotorPin,255);
 analogWrite(blMotorPin,255);
 delay(3000);
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
   channelCalc();
 analogWrite(trMotorPin,calcFR());
 analogWrite(brMotorPin,calcBR());
 analogWrite(tlMotorPin,calcFL());
 analogWrite(blMotorPin,calcBL());
  }


}

void channelCalc()
{
if(pulseIn(transmitter,HIGH) > 4000)
{
  channell = pulseIn(transmitter,HIGH);
  channel2 = pulseIn(transmitter,HIGH);
  channel3 = pulseIn(transmitter,HIGH);
  channel4 = pulseIn(transmitter,HIGH);
  channel5 = pulseIn(transmitter,HIGH);
  channel6 = pulseIn(transmitter,HIGH);
  channel7 = pulseIn(transmitter,HIGH);
  channel8 = pulseIn(transmitter,HIGH);
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
  return (calcThrottle() + tiltLeft()+ calcBackPitch());
}
int calcFL()
{
    return (calcThrottle() + tiltRight()+ calcBackPitch());

}
int calcBL()
{
    return (calcThrottle() + tiltRight()+ calcFrontPitch());

}
int calcBR()
{
    return (calcThrottle() + tiltLeft() + calcFrontPitch());

}

// Calculating Right motion of drone, Cannot add power unless user is throttling drone
int tiltLeft()
{
  if(calcThrottle() != baseLine)
  {
  int roll = getChannel1();
  if(roll >1070 && roll<=1080)
  {
    return 0;
  }
  int add = roll/55;

  if(roll<1070)
  {
    return add;
  }
  return 0;
}
}
// Calculating left motion of drone, Cannot add power unless user is throttling drone

int tiltRight()
{
   if(calcThrottle() != baseLine)
   {
  int roll = getChannel1();
  if(roll >1070 && roll<=1080)
  {
    return 0;
  }
  int add = roll/80;
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
  if(temp<680)
  {
    return baseLine;
  }
  int add = 128 + temp/26;
  temp = add;
  return temp;
}
// Calculating front motion of drone, Cannot add power unless user is throttling drone

int calcFrontPitch()
{
   if(calcThrottle() != [baseLine])
   {
  int pitch = getChannel2();
 if(pitch >1070 && pitch <=1080)
  {
    return 0;
  }
  int pitchAdd=pitch/80;
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
   if(calcThrottle() != baseLine)
   {
 int pitch = getChannel2();
 if(pitch >1070 && pitch <=1080)
  {
    return 0;
  }
  int pitchAdd=pitch/55;
  if(pitch<1070)
  {
    return pitchAdd;
  }
  return 0;
}
}
