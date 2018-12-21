#include <Arduino.h>
extern int channell,channel2,channel3,channel4,channel5,channel6,channel7,channel8;
extern int transmitter= 3;

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
