#include <FastLED.h>
#include <TimeLib.h>

// How many leds in your strip?
#define NUM_LEDS 150
#define DATA_PIN 5
CRGB leds[NUM_LEDS];

//Blynk
#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(10, 11); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
char auth[] = "X-HyqMNIcum5pORDw6g4yFB848FPVDQl";

//https://circuitdigest.com/microcontroller-projects/arduino-i2c-tutorial-communication-between-two-arduino


unsigned long starttime;
unsigned long endtime;
int timersecs;
int currenttimersecs;

String timerstatus = "active";
void setup() {
  // put your setup code here, to run once:
/*DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");
  Blynk.begin(Serial, auth);*/
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  //right score digit start 0 ends 14
  //2nd right score digit start 14 ends 28
  //right clock digit  start 29 ends at 50
  //2nd right clock digit start 50 ends at 71
  //top point 72
  //bottom point 77
  //2nd left clock digit start 79 ends at 100
  //left clock digit start 100 ends at 121
  //left score digit start 122 ends at 136
  //2nd left score digit start 136 ends at 150

  //Colors - Brown, Blue, Cyan, Green, Gold, Grey, LightBlue, Orange, Pink, Red, Silver, Teal, Violet, Yellow, White, Purple
int mins = 5;
int secs= 59;

//start timer
starttime = now();
endtime = starttime + timersecs;

//stop timer on button
timersecs = endtime - now();
timerstatus = "stopped";


//stop timer when time =0 
if (now() ==endtime){
//activate buzzer
timerstatus = "stopped";
}

//reset timer to value
if (timerstatus =="stopped"){
  timersecs = mins*60 + secs;
}

//display time use minute(timersecs) to calculate minutes.
if (timerstatus == "active"){
currenttimersecs = endtime - now();
}
if (timerstatus == "stopped"){
currenttimersecs = timersecs;
}

/*number 1
int istrt=29;
    leds[istrt] = CRGB::White;     
    leds[istrt+1] = CRGB::White; 
    leds[istrt+2] = CRGB::White; 
 
    
    FastLED.show(); 
  //  delay(1000);
    leds[74] = CRGB::Black;  */
/*  for( int i = 14; i < 28; i++) {
    leds[i] = CRGB::Red; 
    leds[i+1] = CRGB::Red; 
    FastLED.show();
    delay(1000);
    leds[i] = CRGB::Black; 
    leds[i+1] = CRGB::Black;   
    FastLED.show(); 
    Serial.println(i);    
    i=i+1;
    }
  for( int i = 100; i < 121; i++) {
    leds[i] = CRGB::Red; 
    leds[i+1] = CRGB::Red; 
    leds[i+2] = CRGB::Red; 
    FastLED.show();
    delay(1000);
    leds[i] = CRGB::Black; 
    leds[i+1] = CRGB::Black;   
    leds[i+2] = CRGB::Black;   
    FastLED.show(); 
    Serial.println(i);    
    i=i+1;
    i=i+1;
    }*/

    
 //     Blynk.run();
}
/*BLYNK_WRITE(V0)
{
  String textIn = param.asStr();
  Serial.print(textIn + "\n");
}
*/
