
#include <ESP8266WiFi.h> 
#include <FirebaseArduino.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#define FIREBASE_HOST "water-strathmore-default-rtdb.firebaseio.com/"      
#define FIREBASE_AUTH "Ub6RnzA7aeOF0sjWfh66z0eSd5wv1fD4ic4ZfUfH"            
#define WIFI_SSID "Incubator"                                  
#define WIFI_PASSWORD "Incubator#2013"   

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
int sensorPin = A0;
void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
}
 Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
}
void loop(void)
{
  // reading analog values
  int sensorValue = analogRead(sensorPin);
  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  Serial.print("Turbidity level is: ");
 Serial.println(sensorValue);
 String fireTurbidity = String(sensorValue);
  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  String fireTemp = String(sensors.getTempCByIndex(0));
  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
  delay(5000);
  Firebase.pushString ("/WaterQuality/Turbidity," fireTurbidity);
  Firebase.pushString ("/WaterQuality/Temperature," fireTemp);

}
