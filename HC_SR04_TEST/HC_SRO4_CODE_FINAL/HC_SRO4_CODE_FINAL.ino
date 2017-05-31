//Test Code and Draft code for HC-SR04 Sonar Sensor 
//Stumper Thumpers
//This sketch tests the HC-SR04 by connecting it directly into
// the arduino board using pins 2,3,4 and 5. 


//Pin variable names are named directly after the jumpers on the
//..sonar sensor
int VCC = 2; //attach pin 2 to VCC
int Trig = 3; // attach pin 3 to Trig
int Echo = 4; //attach pin 4 to Echo
int GND = 5; //attach pin 5 to GND

//Setup function to prepare the pins for use, no return value
void setup() 
{
Serial.begin(9600);  //establishes serial communication at a 
                    //..rate of 9600 bauds(bits per second)  
pinMode (VCC,OUTPUT); //sets VCC/pin 2 as a digital output pin
pinMode (GND,OUTPUT); //sets GND/pin 5 as a digital output pin
}

//Function to convert microseconds into centimeters
 long microsecondsToCentimeters(long microseconds)
 {
 return microseconds / 29 / 2;
 }

 //Function to convert microseconds into inches
 long microsecondsToInches(long microseconds)
 {
 return microseconds / 74 / 2;
 }

//Main portion of the code.
void loop()
{
 //variables to hold the inches, centimeters, and ping duration 
 long in, cm, duration; 

 //Initializes digital output pin VCC(2) for use. The GND(5) pin 
 //..doesn't have to be declared as pins default to LOW
 digitalWrite(VCC, HIGH);
 
 //From the HC-SR04 info sheet:
 // The PING is triggered by a HIGH pulse of 2 or more microseconds.
 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
 pinMode(Trig, OUTPUT); //digital output
 digitalWrite(Trig, LOW);
 delayMicroseconds(2);  //clean-up the pulse
 digitalWrite(Trig, HIGH);
 delayMicroseconds(5);  // actual PING
 digitalWrite(Trig, LOW);

 // The same pin is used to read the signal from the PING: a HIGH
 // pulse whose duration is the time (in microseconds) from the sending
 // of the ping to the reception of its echo off of an object.
 pinMode(Echo,INPUT);
 duration = pulseIn(Echo, HIGH); //get the echo/return of sound

 //Used to convert the return time of the echo into a distance
 in = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);

 Serial.print(inches);
 Serial.print("in, ");
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();

 delay(100);
 }




