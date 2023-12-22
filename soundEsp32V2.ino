// #define SENSOR_PIN 5 // ESP32 pin GPIO18 connected to the OUT pin of the sound sensor

// int lastState = HIGH;  // the previous state from the input pin
// int currentState;      // the current reading from the input pin

// void setup() {
//   // initialize serial communication at 9600 bits per second:
//   Serial.begin(9600);
//   // initialize the ESP32's pin as an input
//   pinMode(SENSOR_PIN, INPUT);
// }

// void loop() {
//   // read the state of the the ESP32's input pin
//   currentState = digitalRead(SENSOR_PIN);

//   if (lastState == HIGH && currentState == LOW)
//     Serial.println("The sound has been detected");
//   else if (lastState == LOW && currentState == HIGH)
//     Serial.println("The sound has disappeared");

//   // save the the last state
//   lastState = currentState;
// }

// #define SENSOR_PIN 5   
// #define LED_PIN 13     

// int lastState = HIGH;   
// int currentState;       
// unsigned long lastClapTime = 0;
// unsigned long debounceDelay = 300; 
// int clapCount = 0; 
// bool isLEDOn = false; 

// void setup() {
//   Serial.begin(9600);
//   pinMode(SENSOR_PIN, INPUT);
//   pinMode(LED_PIN, OUTPUT);
// }

// void loop() {
//   currentState = digitalRead(SENSOR_PIN);
//   if (lastState == HIGH && currentState == LOW && (millis() - lastClapTime) > debounceDelay) {
//     clapCount++; // Increment clap count
//     lastClapTime = millis(); // update the time of the last detected clap
//     delay(100); // Optional delay to avoid detecting multiple claps in quick succession
//   }

//   if (clapCount == 2) {
//     if (!isLEDOn) {
//       digitalWrite(LED_PIN, HIGH); // Turn on the LED
//       Serial.println("Two claps detected - LED ON");
//       isLEDOn = true; // Update LED state flag
//     } else {
//       digitalWrite(LED_PIN, LOW); // Turn off the LED
//       Serial.println(" LED OFF");
//       isLEDOn = false; // Update LED state flag
//     }
//     clapCount = 0; // Reset clap count
//   }

//   lastState = currentState;
// }


//Analog

#define SENSOR_PIN 36    // ESP32 pin GPIO36 connected to the OUT pin of the sound sensor
#define LED_PIN 13       // ESP32 pin GPIO13 connected to the LED

int lastState = HIGH;    // the previous state from the input pin
int currentState;        // the current reading from the input pin
unsigned long lastClapTime = 0; // to store the time of the last detected clap
unsigned long debounceDelay = 300; // debounce time in milliseconds
int clapCount = 0; // count the number of claps
bool isLEDOn = false; // flag to track LED state

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the ESP32's pin to read the analog input
  pinMode(SENSOR_PIN, INPUT);
  // initialize the ESP32's pin to control the LED as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // read the state of the ESP32's analog input pin
  currentState = analogRead(SENSOR_PIN);

  // Check for a detected clap
  if (lastState >= 500 && currentState < 500 && (millis() - lastClapTime) > debounceDelay) {
    clapCount++; // Increment clap count
    lastClapTime = millis(); // update the time of the last detected clap
    delay(100); // Optional delay to avoid detecting multiple claps in quick succession
  }

  // Check if two claps have been detected
  if (clapCount == 2) {
    if (!isLEDOn) {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED
      Serial.println("Two claps detected - LED ON");
      isLEDOn = true; // Update LED state flag
    } else {
      digitalWrite(LED_PIN, LOW); // Turn off the LED
      Serial.println("Two more claps detected - LED OFF");
      isLEDOn = false; // Update LED state flag
    }
    clapCount = 0; // Reset clap count
  }

  // Save the last state
  lastState = currentState;
}
