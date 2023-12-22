
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);
//Servo Motor
int servoPin = 18;  
// Ultrasonic Sensors
#define TRIG_PIN 9
#define ECHO_PIN 10
float duration_us, distance_cm;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd_i2c.init(); 
  lcd_i2c.backlight();
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;

  Serial.print("distance: ");
  Serial.println(distance_cm);

  if(distance_cm < 20){

  lcd_i2c.clear();
  lcd_i2c.setCursor(0, 0);    
  lcd_i2c.print("Trashcan: ");     
  lcd_i2c.setCursor(2, 1);    
  lcd_i2c.print("OPEN"); 
  }
  else{ 
  lcd_i2c.clear(); 
  lcd_i2c.setCursor(0, 0);      
  lcd_i2c.print("Trashcan:");       
  lcd_i2c.setCursor(2, 1);     
  lcd_i2c.print("CLOSED"); 
  }

delay(500);
}
