#include <LCD_I2C.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

LCD_I2C lcd(0x27);//default;

ThreeWire myWire(3,4,2);
RtcDS1302<ThreeWire> Rtc(myWire);
const int PIN_RED   = 5;
const int PIN_GREEN = 6;
const int PIN_BLUE  = 9;

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  lcd.begin();
  Rtc.Begin();
  // RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  // Rtc.SetDateTime(currentTime);
  lcd.backlight();
  lcd.print("Ardie");
  lcd.print("Count: ");
}

void loop() {

RtcDateTime now = Rtc.GetDateTime();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Date: ");
lcd.print(now.Day());
lcd.print("/");
lcd.print(now.Month());
lcd.print("/");
lcd.print(now.Year());
lcd.setCursor(0,1);// Second line;
lcd.print("Time: ");
lcd.print(now.Hour());
lcd.print(": ");
lcd.print(now.Minute());
lcd.print(": ");
lcd.print(now.Second());

// for(int i =0; i < 1000000; i++){
//   lcd.setCursor(9,0);
//   lcd.print(i);
//   delay(1000);
// }


// color code #00C9CC (R = 0,   G = 201, B = 204)
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 255);
  analogWrite(PIN_BLUE,  210);

  delay(1000); // keep the color 1 second

  // color code #F7788A (R = 247, G = 120, B = 138)
  analogWrite(PIN_RED,   250);
  analogWrite(PIN_GREEN, 150);
  analogWrite(PIN_BLUE,  180);

  delay(1000); // keep the color 1 second

  // color code #34A853 (R = 52,  G = 168, B = 83)
  analogWrite(PIN_RED,   50);
  analogWrite(PIN_GREEN, 200);
  analogWrite(PIN_BLUE,  100);

  delay(1000); // keep the color 1 second
}
