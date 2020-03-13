#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial s;
String  i;
WiFiServer server(80);
int data;
 
void setup(){
  Serial.begin(9600);
  i = "";
  
  s.begin(9600,D6,D5);
  WiFi.disconnect();
  delay(3000);
  
  Serial.println("START");
  WiFi.begin("123");

  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();
}

void loop(){
  WiFiClient client = server.available();

  if (!client) { 
    return; 
  }
  
  i = (client.readStringUntil('\r'));
  i.remove(0, 5);
  i.remove(i.length()-9,9);
  
  if (i == "ON"){
    data = 1;
  }else if (i == "OFF"){
    data = 0;
  }
  s.write(data);
}  
