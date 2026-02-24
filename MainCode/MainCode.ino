  #include <dht.h>        // Include library
#define outPin 8        // Defines pin number to which the sensor is connected
#include <SoftwareSerial.h>

  SoftwareSerial nodemcu(2,3);//NodeMCU
dht DHT;                // Creates a DHT object
int sdata1 = 0; // sensor1 data
int sdata2 = 0; // sensor2 data
String cdata; // complete data, consisting of sensors values

int pump = 7;
int pump_motor = 6;
int moisturesensor = A0;
int moisturedata;
int pump_status = 1;


void setup() {
  Serial.begin(9600);
  pinMode(pump,INPUT_PULLUP);
  pinMode(pump_motor,OUTPUT);
  pinMode(moisturesensor,INPUT);  
  nodemcu.begin(9600);
}

void loop() {
  int readData = DHT.read11(outPin);
  pump_status = digitalRead(pump);
  moisturedata = digitalRead(moisturesensor);
  Serial.println(moisturedata);   

  float t = DHT.temperature;        // Read temperature
  float h = DHT.humidity;           // Read humidity

  if(moisturedata >800 ){
    pump_status = 0;
  }

/*
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("°C | ");
  Serial.print((t*9.0)/5.0+32.0);        // Convert celsius to fahrenheit
  Serial.println("°F ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.println("");
*/
//  cdata = cdata+"," + t+","+h+","+pump_status+'\n'; // comma will be used a delimeter
   cdata = cdata+ t+","+h+","+pump_status+'\n'; // comma will be used a delimeter

  Serial.println(cdata); 
  nodemcu.println(cdata);
  cdata = ""; 
  delay(2000); // wait two seconds
}
