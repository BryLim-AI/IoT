#define POWER_PIN  7
#define SIGNAL_PIN A5
int buzzerPin = 8;
int value = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); 
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("Sensor value: ");
  Serial.println(value);

  if(value > 500){
    digitalWrite(buzzerPin, HIGH);
  }
  else{
   digitalWrite(buzzerPin, LOW);
  }

  delay(1000);
}
