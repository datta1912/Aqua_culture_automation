#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
String apiKey = "VXXLAR8P11CA5SMV";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "SRKR_IDEALAB";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Tech$9889";
const char* server = "api.thingspeak.com";
#define DHTPIN D5          //pin where the dht11 is connected
 int rain = A0;
int bs1 = 0;
int ldr = D4;
int bs = 0;
int relay = D0;
DHT dht(DHTPIN, DHT11);
WiFiClient client;
void setup()
{
       Serial.begin(115200);
       delay(10);
       pinMode(ldr,INPUT);
  pinMode(relay,OUTPUT);
       dht.begin();
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED)
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
void loop()
{
   bs = digitalRead(ldr);
 Serial.print("status = ");
Serial.println( bs);
delay(500);
bs1 = analogRead(rain);
 Serial.print("status1 = ");
 Serial.println(bs1);
delay(500);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
 if(bs == HIGH)
{
  digitalWrite(relay,LOW);
}
else
{
  digitalWrite(relay,HIGH);
}
              if (isnan(h) || isnan(t))
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                           
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                              postStr +="&field3=";
                             postStr += String(bs);
                             postStr +="&field4=";
                             postStr += String(bs1);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
 
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
