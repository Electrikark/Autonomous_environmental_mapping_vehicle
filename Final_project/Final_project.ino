// button switch works
// wheels work
// 2 ultrasonic sensors
// rgbs kind of work

#include "rfid1.h"
RFID1 rfid;

#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 30, 33, 26, 24, 22);

// -------- FUNCTION PROTOTYPES --------
void STOP();
void spinMotor(int motorSpeed);
void turnRight(int turnSpeed, int ms);
void turnLeft(int turnSpeed, int ms);
float avg(int dimension);

// -------- MOTOR PINS --------
const int AIN1 = 48;
const int AIN2 = 46;
const int PWMA = 44;

const int BIN1 = 50;
const int BIN2 = 52;
const int PWMB = 53;

// -------- SENSOR VARIABLES --------
int switchVal = analogRead(A0);
float distance = 0.0;
float distance2 = 0.0;

const int trigPin = A10, echoPin = A11;
const int trigPin2 = A12, echoPin2 = A13;

// -------- RGB --------
const int RED = 35;
const int GREEN = 39;
const int BLUE = 37;

// -------- SPEAKER --------
const int SPEAKERPIN = 47;

// -------- MEMORY --------
const int M_SIZE = 10;
int memIndex = 0;
bool memFilled = false;

float memory[2][M_SIZE];

float sum = 0;
float average_left = 1;
float average_right = 1;

// -------- LIGHT SENSOR --------
const int LIGHT_ANALOG = A8;
const int LIGHT_DIGITAL = 31;
int lightLevel = analogRead(LIGHT_ANALOG);

// =====================================================
// SETUP
// =====================================================
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(SPEAKERPIN, OUTPUT);

  pinMode(LIGHT_DIGITAL, INPUT);
  pinMode(38, INPUT_PULLUP);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(47, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Hello");
  delay(5000);
}

float getDistance() {
  float echoTime;
  float calculatedDistance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);
  calculatedDistance = echoTime / 148.0;

  return calculatedDistance;
}

// =====================================================
// MEMORY FUNCTION
// =====================================================
void update_Memory(float leftDist, float rightDist) {
  memory[0][memIndex] = leftDist;
  memory[1][memIndex] = rightDist;

  memIndex++;

  if (memIndex >= M_SIZE) {
    memIndex = 0;
    memFilled = true;
  }
}

// =====================================================
// RGB LED
// =====================================================
void emit_red() {
  analogWrite(RED, 128);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}
//  changed the analog write blue and green as chat said, I'll switch it if it doesn't work out
void emit_green() {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 128);
}

void emit_blue() {
  analogWrite(RED, 0);
  analogWrite(BLUE, 128);
  analogWrite(GREEN, 0);
}
void emit_nothing() {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
}

// =====================================================
// TURN FUNCTIONS
// =====================================================
void turnRight(int turnSpeed, int ms) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, turnSpeed);
  analogWrite(PWMB, turnSpeed);

  delay(ms);
  STOP();
}

void turnLeft(int turnSpeed, int ms) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, turnSpeed);
  analogWrite(PWMB, turnSpeed);

  delay(ms);
  STOP();
}

// =====================================================
// AVERAGE FUNCTION
// =====================================================
float avg(int dimension) {
  float sum = 0;
  int count;

  if (memFilled){
    count = M_SIZE;
  }
  else {
    count = memIndex;
  }
  if (count == 0) {
    return 0;
  }

  for (int i = 0; i < count; i++) {
    sum += memory[dimension][i];
  }

  return sum / count;
}

// =====================================================
// MOTOR CONTROL
// =====================================================
void STOP() {
  spinMotor(0);
}

void spinMotor(int motorSpeed) {
  if (motorSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    Serial.println("A works");

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    Serial.println("B works");
  } else if (motorSpeed < 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }

  analogWrite(PWMA, abs(motorSpeed));
  analogWrite(PWMB, abs(motorSpeed));
}

// =====================================================
// AVOID FUNCTION
// =====================================================
void avoid() {
  spinMotor(-255);
  delay(1000);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);

  delay(1000);
}

float getDistance2() {
  float echoTime2;
  float calculatedDistance1;

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  echoTime2 = pulseIn(echoPin2, HIGH);
  calculatedDistance1 = echoTime2 / 148.0;

  return calculatedDistance1;
}

// =====================================================
// LOOP
// =====================================================
void loop() {
  tone(47, 1000);
  distance = getDistance();
  distance2 = getDistance2();

  switchVal = digitalRead(38);
  lightLevel = analogRead(LIGHT_ANALOG);

  update_Memory(distance, distance2);

  Serial.println(lightLevel);
  Serial.println("Distance of left side = " + String(distance));
  Serial.println("Distance of right side = " + String(distance2));
  Serial.println(String(switchVal));

  if (lightLevel > 700 || !memFilled) {
    STOP();
    emit_nothing();
    emit_red();
    emit_green();
    emit_blue();


    delay(500);

    Serial.print("beginning");
    lcd.print("Turned off");
    if (!memFilled) {
      lcd.clear();
      lcd.print("Not set up yet");
    }
  } 
  else {
    emit_nothing();
    if (switchVal >= 1) {
      
      average_left = avg(0);
      average_right = avg(1);
      float diff = average_left - average_right;
      // MAIN
      if (average_left > 35.0 && average_right > 35.0) {
        emit_nothing();
        emit_green();

        Serial.print("forward");
        lcd.clear();
        lcd.print("FORWARD");
        spinMotor(200);
      } 
      else if (average_left < 20 || average_right < 20) {
        emit_nothing();
        emit_red();
        lcd.clear();
        lcd.print("TOO CLOSE");

        if (average_left < average_right) {
          turnRight(200, 250);
        } 
        else {
          turnLeft(200, 250);
        }
      } 
      else {
          emit_nothing();
          emit_green();
          emit_red();
        if (abs(diff) <= 5) {
          lcd.clear(); 
          lcd.print("STRAIGHT");
          spinMotor(180);
        } 
        else if (diff > 0) {
          lcd.clear(); 
          lcd.print("LEFT");
          turnLeft(180, 150);
        } 
        else {
          lcd.clear(); 
          lcd.print("RIGHT");
          turnRight(180, 150);
    }
      }

      delay(1000);
    } 
    else {
      emit_nothing();
      STOP();
      
    }
  }

  delay(1000);
}
