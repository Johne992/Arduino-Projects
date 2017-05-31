//Draft of Code for Collision Detection system integration 
//John Lewis
//11/12/2015

#include <Servo.h> 
//Subject to change once integrated
int VCC = 2; //Attach pin 2 to VCC
int Trig = 3; //Attach pin 3 to Trig
int Echo = 4; //Attach pin 4 to Echo
int GND =  5; //Attach pin 5 to GND


//Serial communication is not necessary here but we can determine the pins used
void setup(){
  //Set VCC and GND to be digital output pins on the arduino board
  pinMode (VCC,OUTPUT);
  pinMode (GND, OUTPUT);
}

void loop() {

  long duration, inches;
  
  Servo myservo;
  int turn = 45;
  
  //The goal here is not to display distance like in the test but to gauge distance
  //Power the device
  digitalWrite(VCC, HIGH);


  pinMode(Trig, OUTPUT);
  //Output a clean pulse
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);   //shouldn't interfere with the rest of the device, no timer interupt
                          //..only action interupt based on Arduino Library
  digitalWrite(Trig,HIGH);
  delayMicroseconds(5);  //same as above ^
  digitalWrite(Trig, LOW);

   pinMode(Echo,INPUT);
   duration = pulseIn(Echo, HIGH);

  inches = microsecondsToInches(duration); // convert the return time into a distance

  checkforCollision(inches);

}


  long checkforCollision(long inches){

    if(inches < 12){
    //Avoid collision
    myservo.write(turn);
  }
  else{

    //continue on with processes.
  }

}

    //Function to convert microseconds into inches
  long microsecondsToInches(long microseconds)
  {
    return microseconds / 74 / 2;
  }
