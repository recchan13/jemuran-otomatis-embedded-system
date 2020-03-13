#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
const int LDR_PIN = A0;
const int led = 2;
const int rain = 4;
const int relay = 13;
int nyala = 0;
Servo servo;

void setup() {
  s.begin(9600);

  servo.attach(12);
  servo.write(0);

  pinMode(LDR_PIN, INPUT);
  pinMode(led,OUTPUT);
  pinMode(rain,INPUT);
  pinMode(relay,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if(s.available()>0){
    nyala  = s.read();
  }
  
  int water = digitalRead(rain);
  int intensity = analogRead(LDR_PIN);
  
  if (nyala == 1){
    digitalWrite (relay,LOW);
  }else{
    digitalWrite (relay,HIGH);
  }

  if (intensity > 800 || water == 0 ||  nyala == 0){
    servo.write(0);
    digitalWrite(led,LOW);
  }else if (water == 1 && intensity < 800 && nyala == 1){
    servo.write(90);
    digitalWrite(led,HIGH);
  }
}
