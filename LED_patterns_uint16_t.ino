
int latchPin = 5;  
int clockPin = 6; 
int dataPin = 4;  

int buttonPin = 13;
int resetPin = 12;

int pattern = 0;
int patternAmount = 6;

uint16_t leds = 0;    
int ledAmount = 14; 

void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT) ;
  digitalWrite(resetPin, HIGH);
  Serial.begin(9600);

}

void loop() 
{
  
  if(digitalRead(buttonPin))
  {
    ++pattern; 
    if(pattern == patternAmount)
    {
      pattern = 0;
    }
    powerLEDs(false);
    digitalWrite(resetPin, LOW);
    delay(10);
    digitalWrite(resetPin, HIGH);
  }
  switch (pattern)
  {
    case 0:
      spinPattern(2,5,true,150);
      break;
      
    case 1:
      spinPattern(1,13,true,150);
      break;
      
    case 2:
      graduallyChange(0,ledAmount,true,false,150);
      graduallyChange(0,ledAmount,false,false,150);
      delay(1000);
      graduallyChange(0,ledAmount,true,true,150);
      graduallyChange(0,ledAmount,false,true,150);
      delay(1000);
      break;
      
    case 3:
      graduallyChangeHalves(true, true, true, 150);
      delay(1000);
      graduallyChangeHalves(true, false, false, 150);
      delay(1000);          
      break;
      
    case 4:
      graduallyChange(0,ledAmount/2,true,true,150);
      graduallyChange(ledAmount/2,ledAmount,true,false,150);
      
      graduallyChange(0,ledAmount/2,false,false,150);
      graduallyChange(ledAmount/2,ledAmount,false,true,150);
      break;

    case 5:
      for(int i = 0; i < ledAmount/2;++i)
      {
        powerLED(i*2,true);
        powerLED(i*2+1,false);
      }
      updateShiftRegister(leds);
      delay(650);
          
      for(int i = 0; i < ledAmount/2;++i)
      {
        powerLED(i*2,false);
        powerLED(i*2+1,true);
      }
      updateShiftRegister(leds);
      delay(650);
      break;
        
    default:
      break;
      // default statements
  }
  
  //updateShiftRegister(256);
}

void graduallyChange(int from, int to, boolean light, boolean clockwise, int pause)
{ 
  
  for(int i = from; i < to; ++i)
  {
    powerLED(i, light);
    if(!clockwise)
    { 
      
      updateShiftRegister(mirrorLEDs(from,to));
    }
    else
    {
      updateShiftRegister(leds);
    }
    delay(pause);
  }
}

void graduallyChangeHalves(boolean offset, boolean toMiddle,boolean light, int pause)
{ 
  if(offset)
  { 
    if(toMiddle)
    {
      powerLED(0, light);
      updateShiftRegister(leds);   
      delay(pause); 
    }
    else
    {
      powerLED(ledAmount/2, light);
      updateShiftRegister(leds);   
      delay(pause);
    }
  }
  if(toMiddle)
  {
    for(int i = offset; i < ledAmount/2; ++i)
    {
      powerLED(i, light);
      powerLED(ledAmount - i - 1 + offset, light);
      updateShiftRegister(leds);   
      delay(pause);
    }
    if(offset)
    {
      powerLED(ledAmount/2,light);
      updateShiftRegister(leds);   
      delay(pause);
    }
  }
  else
  {
    for(int i = ledAmount/2-offset-1; i >= 0 ; --i)
    {
      powerLED(i + offset, light); 
      powerLED(ledAmount - i-1, light);
      updateShiftRegister(leds);   
      delay(pause);
    }
    if(offset)
    {
      powerLED(0,light);
      updateShiftRegister(leds);   
      delay(pause);
    }
  }
}

void spinPattern(int spinChunk, int gap, boolean clockwise, int pause)
{
  int startOffset = spinChunk/2;
  int chunkAmount = ledAmount/(spinChunk+gap);
  int chunkFirst;
  powerLEDs(false);
  for(int x = 0 ; x < chunkAmount ; ++x)
  { 
    chunkFirst = (spinChunk+gap)*x-startOffset;
    powerLEDs(chunkFirst,chunkFirst+spinChunk,true);
    powerLED(chunkFirst-1,false);
  }

  if(!clockwise)
  {
    updateShiftRegister(mirrorLEDs(0,ledAmount));
  }
  else
  {
    updateShiftRegister(leds);
  }
  
  delay(pause);
  for(int i = 0; i < ledAmount-1; i++)
  {
    for(int x = 0; x < chunkAmount ; ++x)
    { 
      chunkFirst = (spinChunk+gap)*x-startOffset;
      powerLED(i + chunkFirst + spinChunk,true);
      powerLED(i + chunkFirst,false);
    }
    
    if(!clockwise)
    {
      updateShiftRegister(mirrorLEDs(0,ledAmount));
    }
    else
    {
      updateShiftRegister(leds);
    }
    delay(pause);
  }
}

uint16_t mirrorLEDs(int from, int to)
{

  uint16_t mirroredLEDs = leds;

  for(int i = 0; i < to-from; ++i)
  {
    if(isLit(from + i))
    {
      mirroredLEDs += power(2,to-i-1);
      mirroredLEDs -= power(2,from + i);
    }
  }
  return mirroredLEDs;
}


void powerLED(int LED, boolean light)
{ 
   if(LED < 0)
   {
    LED = ledAmount + LED;
   }
   if(LED >= ledAmount){
    LED = LED - ledAmount;
   }
   if(light)
   {
    if(!isLit(LED))
    {
      leds += power(2,LED);
    }
   }
   else
   {
    if(isLit(LED))
    {
      leds -= power(2,LED);    
    }
   }
}

boolean isLit(int LED)
{
  LED = power(2,LED);
  return (leds&LED)==LED;
}

void powerLEDs(int from, int to, boolean light)
{
  for(int i = from; i < to; ++i)
  {
    powerLED(i,power);
  }
}
void powerLEDs(boolean light)
{
  if(light)
  {
    leds = power(2,ledAmount)-1;
  }
  else
  {
    leds = 0;
  }
}

void updateShiftRegister(uint16_t ledsValues)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, (ledsValues));
   shiftOut(dataPin, clockPin, LSBFIRST, (ledsValues >> ledAmount/2));
   digitalWrite(latchPin, HIGH);
} 



int power(int num, int power){
   int x = 1;
   for(int i = 0; i < power; i++){
   
    x*=num;
   }
   return x;
}
