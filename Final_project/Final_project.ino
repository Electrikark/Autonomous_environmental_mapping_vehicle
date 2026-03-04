// button switch works
// wheels work
// 2 ultrasonic sensors
// rgbs kind of work

#include "rfid1.h"
RFID1 rfid;

#include  <LiquidCrystal.h>
LiquidCrystal lcd(22,24,26,28,30,32);


const int AIN1 = 48;
const int AIN2 = 46;
const int PWMA = 44;

const int BIN1 = 50;
const int BIN2 = 52;
const int PWMB = 53;
// initialize means a value is given
int switchVal = analogRead(A0);float distance = 0.0;

const int trigPin = A10, echoPin = A11;
const int trigPin2 = A12, echoPin2 = A13;
const int RED = 35;
const int GREEN = 39;
const int BLUE = 37;
const int M_SIZE = 10
int memIndex = 0;        
bool memFilled = false;  
float memory[2][M_SIZE];
void update_Memory(float leftDist, float rightDist){
  memory[0][memIndex]=leftDist;
  memory[0][memIndex]=rightDist;
  memIndex++
  if (memIndex>M_SIZE){
    memIndex=0;
    memFilled = True;  
}
void emit_red(){
  analogWrite(RED,128);
  analogWrite(BLUE,0);

  analogWrite(GREEN,0);
}
void emit_green(){
  analogWrite(RED,0);
  analogWrite(BLUE,128);

  analogWrite(GREEN,0);
}

void emit_blue(){
  analogWrite(RED,0);
  analogWrite(BLUE,0);

  analogWrite(GREEN,128);
}
float getDistance (){ // defining a function get distacne
  float echoTime, calculatedDistance; // local variables 
  digitalWrite(trigPin,HIGH); // turns on
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);


  echoTime = pulseIn(echoPin, HIGH);

  calculatedDistance= echoTime/148.0;

  return calculatedDistance; // INDICATOR THIS IS NON VOID 
//   // IN THIS CASE THIS NON VOID FUNCITON IS RETURNING A FLOAT VALUE

}
float getDistance2 (){ // defining a function get distacne
  float echoTime2, calculatedDistance1; // local variables 
  digitalWrite(trigPin2,HIGH); // turns on
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);


  echoTime2 = pulseIn(echoPin2, HIGH);

  calculatedDistance1= echoTime2/148.0;

  return calculatedDistance1; // INDICATOR THIS IS NON VOID 
  // IN THIS CASE THIS NON VOID FUNCITON IS RETURNING A FLOAT VALUE

}
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


void setup() {  // void set up only runs 1 iteration 
// ultrasonic sensors
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

  pinMode(38,INPUT_PULLUP); // button
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16,2);
  lcd.print("Hello");


}


void loop() { 
  distance = getDistance();  
  distance2= getDistance2();
  Serial.println("Distance of left side = " + String(distance));
  Serial.println("Distance of right side = " + String(distance2));
  switchVal = digitalRead(38); // switchval is ressassigned to a new value 
  Serial.println(String(distance));
  
  Serial.println(String(switchVal));
  emit_red();
  
  delay(1000);
  emit_green();
  delay(1000);

  emit_blue();
  delay(1000);



  //spinMotor(-200);
  // /boolean value: true or false
  // boolean expression evaluates to true or false
  // if else is a joint conditional statement 
//   if (switchVal >=1){ // turned switch on // inside the expression is a boolean expression returning true or False 
//     if (distance > 15.0){ // 2 boolean expressions in this
//       spinMotor(255);

//     }                       // conditional statements can account for if-elses 
//     else {
//       avoid(); // spin motor, avoid , and and

//     }
//     delay(100); // calling the delay function and giving the functino an argument- the value you give the function 
//   }
  
//   else {
//     spinMotor(0);
//     // Serial.print('\nnot working');
    
//   }
//     delay(100); 
}
// NON VOID FUNCTION RETURNING A VALUE
// declaring the datatype of the non void function 



// defining a function  ( void- doesn't return any value)
