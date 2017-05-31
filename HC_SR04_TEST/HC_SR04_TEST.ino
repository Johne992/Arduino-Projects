/*John Lewis
 * HC-SR04 Distance sensor
 * This will test the distance sensor to make sure it is working
 * properly before we move onto systems integration in our proto
 * -type.
 * 10/14/2015
 */


 const int TRIG = 13; //Sets TRIG = 13
 const int ECHO = 12; //Sets ECHO = 12
 const int LED2 = 11;//Sets LED2 = 11
 const int LED1 = 10;//Sets LED1 =10

 void setup(){
  Serial.begin(9600);//open serial port to send data to pc at 9600
                    //bits per second
  pinMode(TRIG,OUTPUT);//sets pin 13 to be an output
  pinMode(ECHO,INPUT);//sets pin 12 to be an input
  pinMode(LED2,OUTPUT);//Sets pin 11 to be an output
  pinMode(LED1,OUTPUT);//Sets pin 10 to be an input 
 }


void loop(){
  digitalWrite(TRIG, LOW); //Turn Off TRIG to begin
  delay(5);               //give break between on and off
  digitalWrite(TRIG,HIGH);//turn on TRIG
  delay(10);              //longer break
  digitalWrite(TRIG,LOW); //Turn off TRIG

  long dist,dur; //create longs "dist(distance)" an dur(Duration)
  dur = pulseIn(ECHO, HIGH); //Turn on ECHO
  dist = (dur/2)/29.1; // calculate distance (cm) 

  if(dist <4) { //if distance is too close
    digitalWrite(LED1,HIGH); // Turn LED1 on
    digitalWrite(LED2,LOW); // Turn LED2 off
  }else { //If distance is not too close
    digitalWrite(LED1, LOW); //Turn LED1 off
    digitalWrite(LED2, HIGH);//Turn LED2 on
  }
  if(dist >= 200 ||dist <=0){
    Serial.println("Out of Range");  //if distance is more than
                                    //200cm it is out of range
  }else {
    Serial.print(dist); //display distance if not out of range
    Serial.println("cm"); // put out centimeter suffix
  }
  delay(500); // half second reset
}

