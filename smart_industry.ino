#include<Servo.h>
Servo servo_5;
const int pingUltra=3;
const int smokePin=A0;
const int buzzerSm=2;
const int tempSen=A1;
const int fanExTemp=4;
const int pirSensor=10;
const int pirMotor=9;
const int pirBulb=7;

int smoke=0;
int temp=0;
int pir=0;
void setup()
{
servo_5.attach(5);

pinMode(smokePin, INPUT); 
pinMode(buzzerSm, OUTPUT);

pinMode(tempSen, INPUT);
pinMode(fanExTemp, OUTPUT);

pinMode(pirSensor, INPUT); 
  pinMode(pirMotor, OUTPUT);

pinMode(pirBulb, OUTPUT);
}
void loop() {





long duration, entryDis;

pinMode(pingUltra, OUTPUT);  
  
  digitalWrite(pingUltra, LOW); 
  delayMicroseconds(2);  
  digitalWrite(pingUltra, HIGH);  
  delayMicroseconds(5);  
  digitalWrite(pingUltra, LOW);


pinMode(pingUltra, INPUT);

duration= pulseIn(pingUltra, HIGH); 
entryDis= microsecondsToCentimeters(duration);

if (entryDis<30) 
{ 
  servo_5.write(180);
  delay(2000);

}

else{ 
  servo_5.write(0);
}

smoke = analogRead(smokePin);

if (smoke >=210) { 
  digitalWrite(buzzerSm, HIGH);
}
  else{
    digitalWrite(buzzerSm,LOW);
  }
  temp=(-40 + 0.488155*(analogRead(tempSen)-20));
  if(temp>=30){
    digitalWrite(fanExTemp,HIGH);
  }else{
    digitalWrite(fanExTemp,LOW);
  }
  pir=digitalRead(pirSensor);
  if(pir==HIGH)
  {
    digitalWrite(pirMotor,HIGH);
    digitalWrite(pirBulb,HIGH);
  }
  else
  {
    digitalWrite(pirMotor,LOW);
    digitalWrite(pirBulb,LOW);
  }
  Serial.print("dis: ");
  Serial.println(entryDis);
  Serial.print("smoke:");
  Serial.println(smoke);
  Serial.print("temp:");
  Serial.println(temp);
  Serial.print("dete:");
  Serial.println(pir);
  delay(1000);
}

  long microsecondsToCentimeters(long microseconds){
    return microseconds/29/2;
  }

  
    
  
    
  
  

