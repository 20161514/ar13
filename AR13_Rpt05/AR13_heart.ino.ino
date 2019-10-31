#include "LedControlMS.h"

#define NBR_MTX 1 //number of matrices attached is one

LedControl lc=LedControl(4,3,2, NBR_MTX);//

unsigned long delayTime=1200;  // Delay between Frames

// Put values in arrays
byte emptyheart[] =
{
   B00100100,  // First frame of invader #1
   B01011010,
   B10000001,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
};

byte wholeheart[] =
{
  B00000000, // Second frame of invader #1
  B01100110,
  B11111111,
  B11111111, 
  B11111111,
  B01111110,
  B00111100,
  B00011000
};



void setup()
{
    lc.shutdown(0,false);// Wake up displays
//  lc.shutdown(1,false);
    lc.setIntensity(0,5);// Set intensity levels
//  lc.setIntensity(1,5);
    lc.clearDisplay(0); // Clear Displays
//  lc.clearDisplay(1);
}


//  Take values in Arrays and Display them
void semptyheart()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,emptyheart[i]);
  }
}

void swholeheart()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,wholeheart[i]);
  }
}



void loop()
{

    semptyheart();
    delay(delayTime);



    swholeheart();
    delay(delayTime);


}
