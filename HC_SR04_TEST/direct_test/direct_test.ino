//Test Code and Draft code for HC-SR04 Sonar Sensor 
//Stumper Thumpers
//This sketch tests the HC-SR04 by connecting it directly into
// the arduino board using pins 2,3,4 and 5. 


//Pin variable names are named directly after the jumpers on the
//..sonar sensor
int VCC = 22; //attach pin 2 to VCC
int Trig = 24; // attach pin 3 to Trig
int Echo = 26; //attach pin 4 to Echo
int GND = 28; //attach pin 5 to GND

//Setup function to prepare the pins for use, no return value
void setup() 
{
Serial.begin(9600);  //establishes serial communication at a 
                    //..rate of 9600 bauds(bits per second)  
pinMode (VCC,OUTPUT); //sets VCC/pin 2 as a digital output pin
pinMode (GND,OUTPUT); //sets GND/pin 5 as a digital output pin
}

//Main portion of the code.
void loop()
{
 //variables to hold the inches, centimeters, and ping duration 
 long in, cm, duration; 

 //Initializes digital output pin VCC(2) for use. The GND(5) pin 
 //..doesn't have to be declared as pins default to LOW
 digitalWrite(VCC, HIGH);
 
 // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
 pinMode(Trig, OUTPUT);
 digitalWrite(Trig, LOW);
 delayMicroseconds(2);
 digitalWrite(Trig, HIGH);
 delayMicroseconds(5);
 digitalWrite(Trig, LOW);

 // The same pin is used to read the signal from the PING))): a HIGH
 // pulse whose duration is the time (in microseconds) from the sending
 // of the ping to the reception of its echo off of an object.
 pinMode(Echo,INPUT);
 duration = pulseIn(Echo, HIGH);

 // convert the time into a distance
 in = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);

 Serial.print(in);
 Serial.print("in, ");
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();

 delay(100);
 }

 long microsecondsToInches(long microseconds)
 {
 // According to Parallax's datasheet for the PING))), there are
 // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
 // second). This gives the distance travelled by the ping, outbound
 // and return, so we divide by 2 to get the distance of the obstacle.
 // See:  http://www.parallax.com/dl/docs/prod/acc/28015-PI...
 return microseconds / 74 / 2;
 }

 long microsecondsToCentimeters(long microseconds)
 {
 // The speed of sound is 340 m/s or 29 microseconds per centimeter.
 // The ping travels out and back, so to find the distance of the
 // object we take half of the distance travelled.
 return microseconds / 29 / 2;
 }

