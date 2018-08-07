#include <stdlib.h>
#include <Adafruit_NeoPixel.h>

#define LEDs 188         //has to be even please
#define PIN 6
#define pot A0
#define PULSE 1
#define PULSERGB 2
#define BRIGHTNESS 3

String input;
int mode = PULSE;
int factor = 8;                //increasing factor in effect speeds the wave; could alternatively change transmission rate on processing too.
int brightness = 0;
int red = 0;
int green = 0;
int blue = 0;
uint32_t color = 0;
int arr[LEDs] = { 0 };
int currrand = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  strip.begin();
  strip.show();
  input.reserve(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() < 0)
    ;
  
  input = Serial.readStringUntil('\n');
  if(!(input.startsWith("0") || input.startsWith("1") || input.startsWith("2")))
  {
    if(input.equals("p"))
      mode = PULSE;
    if(input.equals("r"))
      mode = PULSERGB;
    if(input.equals("b"))
      mode = BRIGHTNESS;
  }
  
  switch(mode)
  {
    case PULSE:
    {
      brightness = input.toInt(); //serial input = color brightness
      if(brightness > 255)
        brightness = 255;
      if(brightness < 0)
        brightness = 0;
      int curr = 0;
      int temp = brightness;
      int temp2;
      for (int i = 0; i<LEDs/factor; i++) {
        if (curr<LEDs/(2*factor)) {
          arr[curr] = arr[curr+1];
        }
        else if (curr == LEDs/(2*factor)) {
          arr[curr] = brightness;
        }
        else {
          temp2 = arr[curr];
          arr[curr] = temp;
          temp = temp2;
        }
        curr++;
      }
      updateStrip();
      break;
    }
    
    case PULSERGB:
    {
      processRGBInput(input);
      //modified regular pulse with rgb... to be implemented
      break;
    }
    
    case BRIGHTNESS:
    {
      //for Aria: to be implemented
      //brightness = input.toInt();
      //for(int i=0; i<LEDs; i++)
        //strip.setPixelColor(i, strip.Color(brightness,brightness,brightness));
      break;
    }

    default: {;}
  }
}


void processRGBInput(String input) //for serial input: "Color: [r],[g],[b]\n"
{
  if(input.startsWith("C"));
    {
    int comma = 0;
    int commaPrev = 0;
      comma = input.indexOf(",");
      String test = "400";
      green = test.toInt();
      String redS = input.substring(7,comma);
      red = redS.toInt();
      commaPrev = comma;
      comma = input.indexOf(",",commaPrev+1);
      String greenS = input.substring(commaPrev+1,comma);
      green = greenS.toInt();
      commaPrev = comma;
      comma = input.indexOf(",",commaPrev+1);
      String blueS = input.substring(commaPrev+1,comma);
      blue = blueS.toInt();
      uint32_t color = strip.Color(red, green, blue);
    }
   }
    
void updateStrip() {//update strip to agree with arr
  for (int i = 0; i<LEDs; i++) {
    strip.setPixelColor(i, strip.Color(arr[i/factor],0/*arr[i/factor]*/,0/*arr[i/factor]*/));
  }
  strip.show();
}
/*





#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
String input;
int red = 0;
int green = 0;
int blue = 0;
uint32_t color = 0;

void setup() {
 Serial.begin(9600);
 strip.begin();
 strip.show();
 input.reserve(1000);
}

void loop() {
  if(Serial.available() > 0)    //serial input: "Color: [r],[g],[b]\n"
  {
    int comma = 0;
    int commaPrev = 0;
    input = Serial.readStringUntil('\n');
    if(input.startsWith("Color: "));
    {
      comma = input.indexOf(",");
      red = atoi(input.substring(7,comma));
      commaPrev = comma;
      comma = input.indexOf(",",commaPrev+1);
      green = atoi(input.substring(commaPrev+1,comma));
      commaPrev = comma;
      comma = input.indexOf(",",commaPrev+1);
      blue = atoi(input.substring(commaPrev+1,comma));
      uint32_t color = strip.Color(red, green, blue);
    }
    
  }
  
}

*/
