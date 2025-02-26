#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 170 //sets speed of DC Motors
#define MAX_SPEED_OFFSET 20
#define LEFT_LED_PIN 26 //red
#define RIGHT_LED_PIN 43 //green

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ); //front right
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

//pushbutton state
/*
const int buttonPin = 38;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool codeEnabled = true;
*/

Servo myservo;
bool goesFwd=false;
int distance = 100;
int speedSet = 0;


void setup() {
  //include pushbutton on/off controller
  //pinMode(buttonPin, INPUT);
  
  myservo.attach(10);
  myservo.write(111);
  Serial.begin(9600);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  
  int distR = 0;
  int distL = 0;
  delay(40);

  if (distance <=55){
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distR = lookRight();
    delay(200);
    distL = lookLeft();
    delay(200);

    if(distR>=distL){
      turnRight();
      moveStop();

      // Turn on the right turn signal LED
    digitalWrite(RIGHT_LED_PIN, HIGH);
    delay(1000);  // Adjust the delay based on your preference
    digitalWrite(RIGHT_LED_PIN, LOW);
    }else
    {
      turnLeft();
      moveStop();

      // Turn on the left turn signal LED
    digitalWrite(LEFT_LED_PIN, HIGH);
    delay(1000);  // Adjust the delay based on your preference
    digitalWrite(LEFT_LED_PIN, LOW);
    }
  }else
  {
    moveForward();
  }

  Serial.print("Distance: ");
  Serial.println(distance);
  distance = readPing();
}

//servo looks right between the angles of 35-115 degrees
int lookRight(){
  myservo.write(35); //sets the servo angle positions
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(111); //sets the servo angle position
  return distance;
}
//servo looks left between the angles of 180-115 degrees
int lookLeft(){
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(111);
  return distance;
}
int readPing(){
  delay(70);
  int cm=sonar.ping_cm();
  if(cm==0) {
    cm=250;
  }
  return cm;
}
void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void moveForward(){
  if(!goesFwd) 
  {
    goesFwd=true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for(speedSet =0; speedSet < MAX_SPEED; speedSet +=2)
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}
void moveBackward(){
  
    goesFwd=false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    for(speedSet =0; speedSet < MAX_SPEED; speedSet +=2)
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
}
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
}
void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
}
