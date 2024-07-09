const int echo = 34;
const int trig = 32;
int duration = 0;
int distance = 0;
int IR1 = 8;
int IR2 = 12;
int IR3 = 13; 
int LDR = 7;
int led1 = 3;
int led2 = 5;
int led3 = 6;
int val1;
int val2;
int val3;
int val4;

void setup()
{
pinMode(IR1,INPUT);
pinMode(IR2,INPUT);
pinMode(IR3,INPUT);
pinMode(LDR,INPUT);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(trig,OUTPUT); 
  pinMode(echo,INPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trig, HIGH);
delayMicroseconds (1000);
digitalWrite(trig, LOW);
 duration = pulseIn(echo, HIGH);
 distance = (duration / 2) / 28.5;
Serial.println(distance);
val1 = digitalRead(IR1);
val2 = digitalRead(IR2);
val3 = digitalRead(IR3);
val4 = digitalRead(LDR);
analogWrite(5,10);
analogWrite(3,10);
analogWrite(6,10);
if(distance>10){
  analogWrite(5,10);
  analogWrite(3,10);
  analogWrite(6,10);
  delay(100);
}
else{
  digitalWrite(5,LOW);
  digitalWrite(3,LOW);
  digitalWrite(6,LOW);
  delay(100);
  
}
if(val1==1&&val4==0&&val2==1&&val3==1)
{
digitalWrite(3,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);

}
else if(val1==0&&val4==1&&val2==0&&val3==1)
{
analogWrite(3,500);
analogWrite(5,500);
analogWrite(6,20);
delay(3000);
}
else if(val1==0&&val4==1&&val2==1&&val3==0)
{

analogWrite(3,500);
analogWrite(6,500);
analogWrite(5,20);
delay(3000);



}
else if(val1==1&&val4==1&&val2==0&&val3==0)
{

analogWrite(6,500);
analogWrite(5,500);
analogWrite(3,0);

delay(3000);
}
else if(val1==0&&val4==1&&val2==0&&val3==0)
{

analogWrite(6,500);
analogWrite(5,500);
analogWrite(3,500);

delay(3000);
}

else if(val1==1&&val4==1&&val2==1&&val3==1)
{
analogWrite(3,20);
analogWrite(5,20);
analogWrite(6,20);
}

else if(val1==0&&val4==1&&val2==1&&val3==1)
{
analogWrite(3,500);
delay(3000);
}
else if(val1==1&&val4==1&&val2==0&&val3==1)
{

analogWrite(5,500);
analogWrite(3,0);
delay(3000);



}
else if(val1==1&&val4==1&&val2==1&&val3==0)
{

analogWrite(6,500);
analogWrite(5,0);
analogWrite(3,0);

delay(3000);
}
}