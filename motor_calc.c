#include <Arduino.h>

extern int baseLine = 30;
extern bool exm;

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
int tiltLeft(bool expert)
{
  if(expert == true)
  {
   //Take a defined multiplier and shoot up volatage on motors
  }
  if(expert == false)
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
}
// Calculating left motion of drone, Cannot add power unless user is throttling drone

int tiltRight(bool expert)
{
  if(expert == true)
  {
   //Take a defined multiplier and shoot up volatage on motors
  }
  if(expert == false)
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
}

// Essential function to get baseline power for motors
int calcThrottle(bool expert)
{
  if(expert == true)
  {
   //Take a defined multiplier and shoot up volatage on motors
  }
  if(expert == false)
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
}
// Calculating front motion of drone, Cannot add power unless user is throttling drone

int calcFrontPitch(bool expert)
{
  if(expert == true)
  {
   //Take a defined multiplier and shoot up volatage on motors
  }
  if(expert == false)
  {
   if(calcThrottle(expert) != [baseLine])
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
}
// Calculating backwards motion of drone, Cannot add power unless user is throttling drone

int calcBackPitch(bool expert)
{
  if(expert == true)
  {
   //Take a defined multiplier and shoot up volatage on motors
  }
  if(expert == false)
  {

  
   if(calcThrottle(expert) != baseLine)
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
}