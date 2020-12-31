#include <Wire.h>
//Blynk
#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(10, 11); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
char auth[] = "X-HyqMNIcum5pORDw6g4yFB848FPVDQl";

void setup() { 
  Serial.begin(9600);
/*DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");
  Blynk.begin(Serial, auth);*/
}
void loop() { 
  Blynk.run();
}

void sendEvent()
{
/*send team names, 
team score adjustment, 
team color, 
score reset,
time reset confirm, 
buzzer status, 
time 
*/  
}
void receiveEvent()
{
  /* receive current time left, team score
}
