/*
Code for the Uno, controlling the servo and esc. It also communicates
via I2C with the Mega, though it doesn't need to actually send
data to it.

Version 1.01
Date: 12/04/15
Latest Version: Works without Sonar integration. This code would 
have been used to test sonar and see if we could integrate it.
*/

#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#define ADR_UNO 5

//Sonar Values
#define TRIG = 2
#define ECHO = 3
#define Sonar_Max 200

NewPing sonar(TRIG,ECHO,Sonar_Max);
int object = 0;
float turn_right = 45;


//Servo and ESC Values
Servo servo; 
Servo servoEsc; 

float angle; 
int flag_there;
int PIN_SERVO = 9;
int PIN_ESC = 5;


void setup() 
{
  // put your setup code here, to run once:
Serial.begin(115200);  
Wire.begin(ADR_UNO);
Wire.onReceive(receiveEvent);


angle = 90; 
flag_there = 0; 
servo.attach(PIN_SERVO); 
servoEsc.attach(PIN_ESC);
servoEsc.writeMicroseconds(1500);
delay(1000);

}

void loop() {
 

}
void receiveEvent(int howMany) {
  int leftPoint;
  int rightPoint; 
  String out ="";
  while (1 <= Wire.available()) { 
    char c = Wire.read(); 
    Serial.write(c);
    out = out + String(c);  
   }
   leftPoint = out.indexOf('<'); 
   rightPoint = out.indexOf('>',leftPoint +1);
   
   if(leftPoint != rightPoint && rightPoint > leftPoint)
   {
    out = out.substring(leftPoint+1,rightPoint); 
    leftPoint = out.indexOf(',');
    angle = (out.substring(0,leftPoint)).toFloat();
    flag_there = (out.substring(leftPoint+1, out.length())).toInt();
    Serial.println(flag_there);
    Serial.println("/");
    moveServo();
    Serial.println(angle);
   }

   //Code to print that there is an object ahead, mega should 
   //request
}

void moveServo(){

 if(object == 0){
  servo.write(angle);
 }
 else{
  servo.write(turn_right);
 }
 startEsc(); 
}

void startEsc(){
  if(flag_there == 0){
    servoEsc.writeMicroseconds(1550);
  }
  else{
    servoEsc.writeMicroseconds(1500); 
  }
}

int Sonar_Detection() {
  int cm = sonar.ping_cm();  //calculate distance

  if (cm > 0 ){             // between 200 cm and 0 cm
    if ( object == 0){      // check if object was not 1
      object = 1;          // make it equal to 0
    }
  }
  else {                    //when nothing is in range change value 
    if (object == 1){
      object = 0;
    }
  }
  
}


