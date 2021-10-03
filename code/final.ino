

#include <FastLED.h>  //Download the library from: https://github.com/FastLED/FastLED
#define NUM_LEDS  300  //The number of LEDs goes here.
#define DATA_PIN 2 //Connect your addressable LED strip to this pin.
#define CLOCK_PIN 13
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() { 
  Serial.begin(9600);
  
  pinMode(A0, INPUT); //Connect the "ENVELOPE" pin of sound detector to Analog pin 0.
//FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  
  FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  for(int i=0; i<=NUM_LEDS; i++)  //Turn off all the LEDs.
  {
  leds[i] = CRGB::Black;
  }
  FastLED.show(); //Update the LED strip.
  

}
int y,z;
int p(int k)
{if(z!=1)
{
  if(y<600)
  {z=1;
    y=k;
  }
}
 return y;
  Serial.println(y);
  
}

void loop() {
  
  int sensitivity = 120;  //Change the sensitivity from here. ranges from 0 to 1023.
  
  int data = analogRead(A0);
// Serial.println(y);
 const int k=data;
 int s =p(k);
 Serial.println(s);
  data=(data-s+1)*5;
  //Serial.println(data);
   if(data<0)
  {
    data=data*-1;
  }
  //Serial.println(data);
  
      

  if(data > sensitivity)
  { 
  data = sensitivity;
  }

  int val_1 = map(data, 0, sensitivity+1, 0, NUM_LEDS);
 //    Serial.println(val_1);
  
  int val_2 = map(data, 0, sensitivity+1, 0, 255);
  int val_3 = map(data, 0, sensitivity+1, 0, NUM_LEDS/2);
  

/*----------------------------------------------------------
  - 4 styles for sound reactive led strip are given below in
    different lines.
  - uncomment the line which you want to try and comment the
    other lines.
  - By default, "LinearReactive" is uncommented.          
-----------------------------------------------------------*/

//LinearReactive(val_1, 100 /* Change brightness from here. ranges from 0 to 255 */);
 //BrightnessReactive(val_2);
  //CentreProgressive(val_3, 100 /* Change brightness from here. ranges from 0 to 255 */);
EdgeProgressive(val_3, 200 /* Change brightness from here. ranges from 0 to 255 */);
  
  FastLED.show(); //DO NOT MAKE THIS LINE A COMMENT.
}

void LinearReactive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[i] = CHSV(hue+=40,200,brightness);
  }

  for(int i=val+1; i<=NUM_LEDS; i++)
  {
  leds[i].nscale8(10);
  }
}

void BrightnessReactive(int val){
  int hue = 0;
  for(int i=0; i<=NUM_LEDS; i++)
  {
  leds[i] = CHSV(hue+=2,255,val);
  }
}

void CentreProgressive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[(NUM_LEDS/2)+i] = CHSV(hue+=20,255,brightness);
  leds[(NUM_LEDS/2)-i] = CHSV(hue+=20,255,brightness);
  }

  for(int i=val+1; i<=(NUM_LEDS/2); i++)
  {
  leds[(NUM_LEDS/2)+i].nscale8(10);
  leds[(NUM_LEDS/2)-i].nscale8(10);
  }
}

void EdgeProgressive(int val, int brightness){
  int hue = 0;
  for(int i=0; i<=val; i++)
  {
  leds[i] = CHSV(hue+=20,255,brightness);
  leds[NUM_LEDS-i] = CHSV(hue+=20,255,brightness);
  }

  for(int i=val+1; i<=(NUM_LEDS/2); i++)
  {
  leds[i].nscale8(10);
  leds[NUM_LEDS-i].nscale8(10);
  }
}
