#define LED_PIN_1 9
#define LED_PIN_2 11
#define LED_PIN_3 10
#define BUTTON_PIN 7

byte ledState = LOW;
byte lastLedState = LOW;
unsigned long debounceTime = 50;
unsigned long lastTimeButtonWasClicked = 0;

void setup() {
  // put your setup code here, to run once:
   pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
if(millis() - lastTimeButtonWasClicked > debounceTime){
  byte buttonState = digitalRead(BUTTON_PIN);
// escape this loop if value is the same.
  if(buttonState != lastLedState){
    lastLedState = buttonState;
    lastTimeButtonWasClicked = millis();
    if(buttonState == LOW){
      ledState = (ledState == HIGH)? LOW : HIGH;
      digitalWrite(LED_PIN_1, ledState);
      digitalWrite(LED_PIN_2, ledState);
      digitalWrite(LED_PIN_3, ledState);

    }
  }
}
  // if(digitalRead(BUTTON_PIN) == HIGH){

  //   digitalWrite(LED_PIN_1, HIGH);
  //   digitalWrite(LED_PIN_2, LOW);
  //   digitalWrite(LED_PIN_3, LOW);
  //   delay(1000);
  //   digitalWrite(LED_PIN_1, LOW);
  //   digitalWrite(LED_PIN_2, HIGH);
  //   digitalWrite(LED_PIN_3, LOW);
  //   delay(1000);
  //   digitalWrite(LED_PIN_1, LOW);
  //   digitalWrite(LED_PIN_2, LOW);
  //   digitalWrite(LED_PIN_3, HIGH);
  //   delay(1000);
  // }
  // else{
  //   digitalWrite(LED_PIN_1, LOW);
  //   digitalWrite(LED_PIN_2, LOW);
  //   digitalWrite(LED_PIN_3, LOW);
  // }

  // digitalWrite(LED_PIN_1, HIGH);
  // digitalWrite(LED_PIN_2, LOW);
  // digitalWrite(LED_PIN_3, LOW);
  // delay(1000);
  // digitalWrite(LED_PIN_1, LOW);
  // digitalWrite(LED_PIN_2, HIGH);
  // digitalWrite(LED_PIN_3, LOW);
  // delay(1000);
  // digitalWrite(LED_PIN_1, LOW);
  // digitalWrite(LED_PIN_2, LOW);
  // digitalWrite(LED_PIN_3, HIGH);
  // delay(1000);

  // // Fade in and out.
  // for (int i = 0; i <= 255; i++){
  //   analogWrite(LED_PIN, i);
  //   delay(10);
  // }

  // for(int i = 255; i >= 0; i--){
  //   analogWrite(LED_PIN, i);
  //   delay(10);
  // }

}
