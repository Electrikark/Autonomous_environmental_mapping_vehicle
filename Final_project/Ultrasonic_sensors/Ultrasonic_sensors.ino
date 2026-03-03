#include "rfid1.h"
RFID1 rfid;

#include  <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

// this works!
const int AIN1 = 5;
const int AIN2 = 6;
const int PWMA = 7;

const int BIN1 = 4;
const int BIN2 = 3;
const int PWMB = 2;
// initialize means a value is given
int switchVal = analogRead(A0); // digital values may include 0 or 1  
// declaring a datatype is assigning 
float distance = 0.0;

const int trigPin = 13, echoPin = 12; // first ultrasonic sensor
const int trigPin_2 = 11, echoPin_2 = 10; // second ultrasonic sensor

void setup() {  // void set up only runs 1 iteration 
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(11,INPUT_PULLUP);

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate


}

void loop() { 

  // Serial.println("Distance = " + String(getDistance()));
  distance = getDistance();  
  switchVal = digitalRead(11); // switchval is ressassigned to a new value 
  Serial.println(String(distance));
  Serial.println(String(switchVal));

  //spinMotor(-200);
  // /boolean value: true or false
  // boolean expression evaluates to true or false
  // if else is a joint conditional statement 
  if (switchVal >=1){ // turned switch on // inside the expression is a boolean expression returning true or False 
    if (distance > 15.0){ // 2 boolean expressions in this
      spinMotor(255);

    }                       // conditional statements can account for if-elses 
    else {
      avoid(); // spin motor, avoid , and and

    }
    delay(100); // calling the delay function and giving the functino an argument- the value you give the function 
  }
  
  else {
    spinMotor(0);
    // Serial.print('\nnot working');
    
  }
    delay(100);


  
}
// NON VOID FUNCTION RETURNING A VALUE
// declaring the datatype of the non void function 
float getDistance (){ // defining a function get distacne
  float echoTime, calculatedDistance; // local variables 
  digitalWrite(trigPin,HIGH); // turns on
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);


  echoTime = pulseIn(echoPin, HIGH);

  calculatedDistance= echoTime/148.0;

  return calculatedDistance; // INDICATOR THIS IS NON VOID 
  // IN THIS CASE THIS NON VOID FUNCITON IS RETURNING A FLOAT VALUE

}
// defining a function  ( void- doesn't return any value)
void spinMotor(int motorSpeed){ 
  
  // conditional
  if(motorSpeed>0){
        // forward on for motor a
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    Serial.println("A works");

    // forward on for motor B
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW); // all it does turn the forward or reverse signal
    Serial.println("B works");
  }
  else if (motorSpeed<0){
    //Backwards
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    // backwards  on for motor B
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH); // all it does turn the forward or reverse signal 


  }
  else {
      //OFF
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

    // OFF
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW); // all it does turn the forward or reverse signal 

  }

    analogWrite(PWMA, abs(motorSpeed) ); // analog write CANNOT BE NEGATIVE 
    analogWrite(PWMB,  abs(motorSpeed));

}
// function calling 2 other functions
void avoid(){  // usre defined function 
  spinMotor(-255);
  delay(1000);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH); // all it does turn the forward or reverse signal 
  analogWrite(PWMA, abs(255)); // analog write CANNOT BE NEGATIVE 
  analogWrite(PWMB,  abs(255));
  delay(1000);
}

// so when the 

