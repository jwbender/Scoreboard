#include <Wire.h>
#include <TimeLib.h>
//LED
#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 5
CRGB leds[150];

int a=0; //define the first led of first display
int b=14;
int c=29;
int d=50;
int e=79;
int f=100;
int g=122;
int h=136;

#include <LEDMatrixDriver.hpp>
//team names
const uint8_t LEDMATRIX_CS_PIN1 = 9;//one team
const uint8_t LEDMATRIX_CS_PIN2 = 10;//other team

// Define LED Matrix dimensions (0-n) - eg: 32x8 = 31x7
const int LEDMATRIX_WIDTH = 63;  
const int LEDMATRIX_HEIGHT = 7;
const int LEDMATRIX_SEGMENTS = 8;
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);
int x=0, y=0, x2=0;   // start top left

byte font[95][8] = { {0,0,0,0,0,0,0,0}, // SPACE
                     {0x10,0x18,0x18,0x18,0x18,0x00,0x18,0x18}, // EXCL
                     {0x28,0x28,0x08,0x00,0x00,0x00,0x00,0x00}, // QUOT
                     {0x00,0x0a,0x7f,0x14,0x28,0xfe,0x50,0x00}, // #
                     {0x10,0x38,0x54,0x70,0x1c,0x54,0x38,0x10}, // $
                     {0x00,0x60,0x66,0x08,0x10,0x66,0x06,0x00}, // %
                     {0,0,0,0,0,0,0,0}, // &
                     {0x00,0x10,0x18,0x18,0x08,0x00,0x00,0x00}, // '
                     {0x02,0x04,0x08,0x08,0x08,0x08,0x08,0x04}, // (
                     {0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x20}, // )
                     {0x00,0x10,0x54,0x38,0x10,0x38,0x54,0x10}, // *
                     {0x00,0x08,0x08,0x08,0x7f,0x08,0x08,0x08}, // +
                     {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08}, // COMMA
                     {0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00}, // -
                     {0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06}, // DOT
                     {0x00,0x04,0x04,0x08,0x10,0x20,0x40,0x40}, // /
                     {0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38}, // 0
                     {0x04,0x0c,0x14,0x24,0x04,0x04,0x04,0x04}, // 1
                     {0x00,0x30,0x48,0x04,0x04,0x38,0x40,0x7c}, // 2
                     {0x00,0x38,0x04,0x04,0x18,0x04,0x44,0x38}, // 3
                     {0x00,0x04,0x0c,0x14,0x24,0x7e,0x04,0x04}, // 4
                     {0x00,0x7c,0x40,0x40,0x78,0x04,0x04,0x38}, // 5
                     {0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38}, // 6
                     {0x00,0x7c,0x04,0x04,0x08,0x08,0x10,0x10}, // 7
                     {0x00,0x3c,0x44,0x44,0x38,0x44,0x44,0x78}, // 8
                     {0x00,0x38,0x44,0x44,0x3c,0x04,0x04,0x78}, // 9
                     {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, // :
                     {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x08}, // ;
                     {0x00,0x10,0x20,0x40,0x80,0x40,0x20,0x10}, // <
                     {0x00,0x00,0x7e,0x00,0x00,0xfc,0x00,0x00}, // =
                     {0x00,0x08,0x04,0x02,0x01,0x02,0x04,0x08}, // >
                     {0x00,0x38,0x44,0x04,0x08,0x10,0x00,0x10}, // ?
                     {0x00,0x30,0x48,0xba,0xba,0x84,0x78,0x00}, // @
                     {0x00,0x1c,0x22,0x42,0x42,0x7e,0x42,0x42}, // A
                     {0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x7c}, // B
                     {0x00,0x3c,0x44,0x40,0x40,0x40,0x44,0x7c}, // C
                     {0x00,0x7c,0x42,0x42,0x42,0x42,0x44,0x78}, // D
                     {0x00,0x78,0x40,0x40,0x70,0x40,0x40,0x7c}, // E
                     {0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x40}, // F
                     {0x00,0x3c,0x40,0x40,0x5c,0x44,0x44,0x78}, // G
                     {0x00,0x42,0x42,0x42,0x7e,0x42,0x42,0x42}, // H
                     {0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x7e}, // I
                     {0x00,0x7e,0x02,0x02,0x02,0x02,0x04,0x38}, // J
                     {0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44}, // K
                     {0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7c}, // L
                     {0x00,0x82,0xc6,0xaa,0x92,0x82,0x82,0x82}, // M
                     {0x00,0x42,0x42,0x62,0x52,0x4a,0x46,0x42}, // N
                     {0x00,0x3c,0x42,0x42,0x42,0x42,0x44,0x38}, // O
                     {0x00,0x78,0x44,0x44,0x48,0x70,0x40,0x40}, // P
                     {0x00,0x3c,0x42,0x42,0x52,0x4a,0x44,0x3a}, // Q
                     {0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44}, // R
                     {0x00,0x38,0x40,0x40,0x38,0x04,0x04,0x78}, // S
                     {0x00,0x7e,0x90,0x10,0x10,0x10,0x10,0x10}, // T
                     {0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x3e}, // U
                     {0x00,0x42,0x42,0x42,0x42,0x44,0x28,0x10}, // V
                     {0x80,0x82,0x82,0x92,0x92,0x92,0x94,0x78}, // W
                     {0x00,0x42,0x42,0x24,0x18,0x24,0x42,0x42}, // X
                     {0x00,0x44,0x44,0x28,0x10,0x10,0x10,0x10}, // Y
                     {0x00,0x7c,0x04,0x08,0x7c,0x20,0x40,0xfe}, // Z
                      // (the font does not contain any lower case letters. you can add your own.)
                  };    
                // Marquee speed
const int ANIM_DELAY =80;  
String teamname;
String teamcolor;
int leftoriscore=100;
int leftnewscore;
int rightoriscore=100;
int rightnewscore;

int score10;
int score1;


void setup() { 
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  lmd.setEnabled(true);
  lmd.setIntensity(10);   // 0 = low, 10 = high
}
void loop() { 

if (leftoriscore != leftnewscore){
  score10 = leftnewscore /10;
  displayscore(score10,0); 
  score1 = leftnewscore - (score10*10);
  displayscore(score1,14); 
}


if (rightoriscore != rightnewscore){
  score10 = rightnewscore /10;
  displayscore(score10,122); 
  score1 = rightnewscore - (score10*10);
  displayscore(score1,136); 
}

diplayteamname();  
}

void displayteamname(){
  char text[] = teamname;
  int len = strlen(text);
  while(marq==0){
  // ----------Draw the text to the current position
    drawString(text, len, x, 0);
    lmd.display();
  // Wait to let the human read the display
    delay(ANIM_DELAY);
  // Advance to next coordinate
    if( --x < len * -8 )
      x = LEDMATRIX_WIDTH;
    if (x ==63){
      marq=1;
      sprt=0;
    }
  }
}

void drawString(char* text, int len, int x, int y ) 
// * This function draws a string of the given length to the given position.
{
  for( int idx = 0; idx < len; idx ++ )
  {
    int c = text[idx] - 64;

    // stop if char is outside visible area
    if( x + idx * 8  > LEDMATRIX_WIDTH )
      return;

    // only draw if char is visible
    if( 8 + x + idx * 8 > 0 )
      drawSprite( font[c], x + idx * 8, y, 8, 8 );
  }
}

void displayscore(int num, int istrt){
//this function is for displays with 2 leds per segment
//clear scoreboard
  for( int i = 0; i < 28; i++) {
    leds[i] = CRGB::Black;  
    FastLED.show(); 
    i=i+1;
  }
  
  if (num==1){
    leds[istrt] = CRGB::Red;
    leds[istrt+1] = CRGB::Red;
    leds[istrt+8] = CRGB::Red;
    leds[istrt+9] = CRGB::Red;
    FastLED.show();
  }
  if (num==2){
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red; 
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;     
    FastLED.show();
  }
  if (num==3){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;     
    FastLED.show();  
  }
  if (num==4){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red;   
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;       
    FastLED.show();  
  }
  if (num==5){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;            
    FastLED.show();  
  }
  if (num==6){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;            
    FastLED.show();  
  }
  if (num==7){
    leds[istrt] = CRGB::Red;
    leds[istrt+1] = CRGB::Red;
    leds[istrt+8] = CRGB::Red;
    leds[istrt+9] = CRGB::Red;
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;   
    FastLED.show();  
  }
  if (num==8){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;            
    FastLED.show(); 
  }
  if (num==9){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red;     
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;            
    FastLED.show(); 
  }
  if (num==0){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;      
    FastLED.show(); 
  }
}

void displaytime(int num, int istrt){
//this function is for displays with 3 leds per segment
//clear scoreboard
  for( int i = 0; i < 28; i++) {
    leds[i] = CRGB::Black;  
    FastLED.show(); 
    i=i+1;
  }
  if (num==1){
    leds[istrt] = CRGB::Red;     
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    FastLED.show();
  }
  if (num==2){
    leds[istrt] = CRGB::Red;     
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red; 
    leds[istrt+18] = CRGB::Red; 
    leds[istrt+19] = CRGB::Red;
    leds[istrt+20] = CRGB::Red;   
    FastLED.show();
  }
  if (num==3){
    leds[istrt] = CRGB::Red;     
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red;   
    FastLED.show();  
  }
  if (num==4){
    leds[istrt] = CRGB::Red;     
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red;     
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red;       
    FastLED.show();  
  }
  if (num==5){
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red;         
    FastLED.show();  
  }
  if (num==6){
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red; 
    leds[istrt+18] = CRGB::Red;
    leds[istrt+19] = CRGB::Red; 
    leds[istrt+20] = CRGB::Red;             
    FastLED.show();  
  }
  if (num==7){
    leds[istrt] = CRGB::Red;     
    leds[istrt+1] = CRGB::Red; 
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    FastLED.show();  
  }
  if (num==8){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red; 
    leds[istrt+18] = CRGB::Red;
    leds[istrt+19] = CRGB::Red; 
    leds[istrt+20] = CRGB::Red;     
    FastLED.show(); 
  }
  if (num==9){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+9] = CRGB::Red; 
    leds[istrt+10] = CRGB::Red; 
    leds[istrt+11] = CRGB::Red;
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red;           
    FastLED.show(); 
  }
  if (num==0){
    leds[istrt] = CRGB::Red; 
    leds[istrt+1] = CRGB::Red;
    leds[istrt+2] = CRGB::Red; 
    leds[istrt+3] = CRGB::Red;     
    leds[istrt+4] = CRGB::Red; 
    leds[istrt+5] = CRGB::Red; 
    leds[istrt+6] = CRGB::Red; 
    leds[istrt+7] = CRGB::Red; 
    leds[istrt+8] = CRGB::Red; 
    leds[istrt+12] = CRGB::Red; 
    leds[istrt+13] = CRGB::Red;
    leds[istrt+14] = CRGB::Red; 
    leds[istrt+15] = CRGB::Red; 
    leds[istrt+16] = CRGB::Red; 
    leds[istrt+17] = CRGB::Red; 
    leds[istrt+18] = CRGB::Red;
    leds[istrt+19] = CRGB::Red; 
    leds[istrt+20] = CRGB::Red;       
    FastLED.show(); 
  }
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  //Receive team name, color and score
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
void sendEvent()
{
  //send current time, team score
}
