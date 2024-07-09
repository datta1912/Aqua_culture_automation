const int motor1Input1 = 31; // Input 1 for motor 1 (Front Left)
const int motor1Input2 = 32; // Input 2 for motor 1 (Front Left)
const int motor2Input1 = 2;  // Input 1 for motor 2 (Front Right)
const int motor2Input2 = 3;  // Input 2 for motor 2 (Front Right)
const int motor3Input1 = 8;  // Input 1 for motor 3 (Rear Left)
const int motor3Input2 = 9;  // Input 2 for motor 3 (Rear Left)
const int motor4Input1 = 11; // Input 1 for motor 4 (Rear Right)
const int motor4Input2 = 10; // Input 2 for motor 4 (Rear Right)
const int motorPin1 =12;  // Connect to one of the input pins of the H-bridge
const int motorPin2 = 13;  // Connect to the other input pin of the H-bridge
const int trigPin = 53; // Trig pin of the ultrasonic sensor connected to Arduino pin 9
const int echoPin = 51; // Echo pin of the ultrasonic sensor connected to Arduino pin 10
float distance_cm;
void stopMotor();
void stophead();
float ultson();
char readCommand();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void headright();
void headleft();
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1Input1, OUTPUT);
  pinMode(motor1Input2, OUTPUT);
  pinMode(motor2Input1, OUTPUT);
  pinMode(motor2Input2, OUTPUT);
  pinMode(motor3Input1, OUTPUT);
  pinMode(motor3Input2, OUTPUT);
  pinMode(motor4Input1, OUTPUT);
  pinMode(motor4Input2, OUTPUT);
  Serial.begin(9600);
  // Stop the motors at the beginning
  stopMotor();
 // stophead();
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  pinMode(trigPin, OUTPUT); // Set trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Set echoPin as an INPUT

}

void loop() {
  distance_cm = ultson();
if(distance_cm>30)
{
  if (Serial.available() >0) {
    char com = readCommand();
    Serial.print("COM : ");
    Serial.println(com);
    switch (com) {
      case 'F':
      case 'f':
        moveForward();
        break;
      case 'B':
      case 'b':
        moveBackward();
        break;
      case 'L':
      case 'l':
        turnLeft();
        break;
      case 'R':
      case 'r':
        turnRight();
        break;
      case 'S':
      case 's':
        stopMotor();
        break;
      case 'J':
      case 'j':
        headright();
        break;
      case 'K':
      case 'k':
        headleft();
        break;
      default:
        // Invalid command or do nothing
        break;
    }
  }
   
 }
  else {
    headleft();
    distance_cm = ultson();
  }
  delay(1000);
}

char readCommand() {
  if(Serial.available()>0){
    char com = Serial.read();
    return com;
  }
  return 'N';
  }
  void moveForward() {
    
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
  digitalWrite(motor3Input1, HIGH);
  digitalWrite(motor3Input2, LOW);
  digitalWrite(motor4Input1, HIGH);
  digitalWrite(motor4Input2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
  digitalWrite(motor3Input1, LOW);
  digitalWrite(motor3Input2, HIGH);
  digitalWrite(motor4Input1, LOW);
  digitalWrite(motor4Input2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
  digitalWrite(motor3Input1, HIGH);
  digitalWrite(motor3Input2, LOW);
  digitalWrite(motor4Input1, LOW);
  digitalWrite(motor4Input2, HIGH);
}

void turnRight() {
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
  digitalWrite(motor3Input1, LOW);
  digitalWrite(motor3Input2, HIGH);
  digitalWrite(motor4Input1, HIGH);
  digitalWrite(motor4Input2, LOW);
}
void headright(){
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        delay(150);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
}
void headleft(){
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        delay(150);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
}
void stopMotor() {
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, LOW);
  digitalWrite(motor3Input1, LOW);
  digitalWrite(motor3Input2, LOW);
  digitalWrite(motor4Input1, LOW);
  digitalWrite(motor4Input2, LOW);
}
void stophead(){
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
}
float  ultson(){
  long duration;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, and calculate the distance in centimeters (cm) and inches (in)
 duration = pulseIn(echoPin, HIGH);
  distance_cm = duration * 0.034 / 2; // Speed of sound is 340 m/s or 0.034 cm/μs
  
  // Print the distance on the Serial Monitor
  Serial.print("Distance in cm: ");
  Serial.println(distance_cm);
  return distance_cm;
}