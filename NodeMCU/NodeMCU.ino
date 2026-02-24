#define BLYNK_TEMPLATE_ID "TMPL69kFbDZWd"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "l9SkldpBkgXU2bBnPYVY1MUXRSORuqR9"

#define BLYNK_PRINT Serial
//#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//#include <SoftwareSerial.h>
#include <SPI.h>

BlynkTimer timer;
//SimpleTimer timer;

char ssid[] = "ValienTeam_EXT";  // type your wifi name
char pass[] = "rychelle@16";  // type your wifi password
char auth[] = BLYNK_AUTH_TOKEN;

 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors


//int firstVal, secondVal,thirdVal; // sensors 
float firstVal, secondVal,thirdVal,fourthVal; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V3, millis() / 1000);
}
 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Blynk.begin(auth, ssid, pass);
   
    // Setup a function to be called every second
     timer.setInterval(2000L,sensorvalue1); 
     timer.setInterval(2000L,sensorvalue2); 
     timer.setInterval(2000L,sensorvalue3);
}





void loop() {
  if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }

  if (Serial.available() > 0 ) 
  {
//    Serial.print("received"); 
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    Serial.println( myString);

  // new code
String l = getValue(myString, ',', 0); //
String m = getValue(myString, ',', 1); //
String n = getValue(myString, ',', 2); //

firstVal = l.toInt(); //PH
secondVal = m.toInt(); //SOIL
thirdVal = n.toInt();
//firstVal = l.toFloat(); //PH
//secondVal = m.toFloat(); //SOIL
//sensorvalue1();
//sensorvalue2();
//sensorvalue3();
    
    if( rdata == '\n')
    {
   
      Serial.println("received"); 
     
      // 

/*
  Serial.println("l:");
  Serial.println(firstVal);
  Serial.println("m:");
  Serial.println(secondVal);
  Serial.println("n:");
  Serial.println(thirdVal);
    // Setup a function to be called every second
*/
  myString = "";
   Serial.print(myString); 
// end new code
    }
  }
}


void sensorvalue1()
{
int sdata = firstVal;
// int sdata =11;
  Serial.println(sdata);
//int sdata =11;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, sdata);
 
}
void sensorvalue2()
{
int sdata = secondVal;
//int sdata =12;
Serial.println(sdata);
//int sdata =12;
// You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, sdata);
 
}
void sensorvalue3()
{
int sdata = thirdVal;
//int sdata = 10.4612;
// sdata =12;
// You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, sdata);
 
}

 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

BLYNK_WRITE(V3) {
  digitalWrite(2, param.asInt());
}
