// button switch works
// wheels work
// 2 ultrasonic sensors
// rgbs kind of work

#include "rfid1.h"
RFID1 rfid;

#include <LiquidCrystal.h>
LiquidCrystal lcd(22,24,26,28,30,32);

const int AIN1 = 48;
const int AIN2 = 46;
const int PWMA = 44;

const int BIN1 = 50;
const int BIN2 = 52;
const int PWMB = 53;

int switchVal = analogRead(A0);
float distance = 0.0;
float distance2 = 0.0;

const int trigPin = A10, echoPin = A11;
const int trigPin2 = A12, echoPin2 = A13;

const int RED = 35;
const int GREEN = 39;
const int BLUE = 37;

const int M_SIZE = 10;
int memIndex = 0;
bool memFilled = false;
float memory[2][M_SIZE];

const int LIGHT_ANALOG = A8;
const int LIGHT_DIGITAL = 31;
int lightLevel = analogRead(LIGHT_ANALOG);

void update_Memory(float leftDist, float rightDist) {
  memory[0][memIndex] = leftDist;
  memory[1][memIndex] = rightDist;

  memIndex++;
  if (memIndex >= M_SIZE) {
    memIndex = 0;
    memFilled = true;
  }
}

void emit_red() {
  analogWrite(RED,128);
  analogWrite(BLUE,0);
  analogWrite(GREEN,0);
}

void emit_green() {
  analogWrite(RED,0);
  analogWrite(BLUE,128);
  analogWrite(GREEN,0);
}

void emit_blue() {
  analogWrite(RED,0);
  analogWrite(BLUE,0);
  analogWrite(GREEN,128);
}

float getDistance() {
  float echoTime, calculatedDistance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  echoTime = pulseIn(echoPin, HIGH);
  calculatedDistance = echoTime/148.0;

  return calculatedDistance;
}

float getDistance2() {
  float echoTime2, calculatedDistance1;
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);

  echoTime2 = pulseIn(echoPin2, HIGH);
  calculatedDistance1 = echoTime2/148.0;

  return calculatedDistance1;
}

void spinMotor(int motorSpeed) {
  if (motorSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    Serial.println("A works");

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    Serial.println("B works");
  }
  else if (motorSpeed < 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }

  analogWrite(PWMA, abs(motorSpeed));
  analogWrite(PWMB, abs(motorSpeed));
}

void avoid() {
  spinMotor(-255);
  delay(1000);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, abs(255));
  analogWrite(PWMB, abs(255));
  delay(1000);
}

void setup() {
  // pin 13 photoresistor digital
  // Pin A8 Analog

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

  pinMode(LIGHT_DIGITAL, INPUT);

  pinMode(38,INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Hello");
}

void loop() {
  distance = getDistance();
  distance2 = getDistance2();
  switchVal = digitalRead(38);
  lightLevel = analogRead(LIGHT_ANALOG);

  update_Memory(distance, distance2);
  update_Memory(distance, distance2);

  Serial.println(lightLevel);
  Serial.println("Distance of left side = " + String(distance));
  Serial.println("Distance of right side = " + String(distance2));
  Serial.println(String(switchVal));

  // for (int i = 0; i < M_SIZE; i++){
  //   Serial.println(memory[0][i]);
  //   Serial.println(memory[1][i]);
  // }

  delay(1000);

  // for (int i = 0; i < M_SIZE; i++) {
  //   Serial.print("L["); Serial.print(i); Serial.print("]=");
  //   Serial.print(memory[0][i]);
  //   Serial.print(" R["); Serial.print(i); Serial.print("]=");
  //   Serial.println(memory[1][i]);
  // }
}

// emit_red();
// delay(1000);
// emit_green();
// delay(1000);

// emit_blue();
// delay(1000);

// spinMotor(-200);
// boolean value: true or false
// boolean expression evaluates to true or false
// if else is a joint conditional statement

// if (switchVal >=1){
//   if (distance > 15.0){
//     spinMotor(255);
//   }
//   else {
//     avoid();
//   }
//   delay(100);
// }
// else {
//   spinMotor(0);
// }
// delay(100);

// NON VOID FUNCTION RETURNING A VALUE
// declaring the datatype of the non void function

// defining a function (void - doesn't return any value)
