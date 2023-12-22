// Include the Servo library 
#include <ESP32Servo.h> 
// Declare the Servo pin 
int servoPin = 18; 
// Create a servo object 
Servo Servo1; 

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
   // Make servo go to 0 degrees 
   // Make servo go to 180 degrees 
   Servo1.write(0); 
   delay(1000); 
   Servo1.write(150); 
   delay(1000); 
}