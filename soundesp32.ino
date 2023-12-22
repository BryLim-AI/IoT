int sound_digital = 0;
int sound_analog = 4;


void setup() {
  // put your setup code here, to run once:
 pinMode(sound_digital, INPUT);
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int val_digital = digitalRead(sound_digital);
  int val_analog = analogRead(sound_analog);

  Serial.print(val_analog);
  Serial.print("\t");
  Serial.println(val_digital);


  if(val_digital == HIGH){
    Serial.println("Sound Detected");
  }
  else{
    Serial.println("Not Detected");
  }

  delay(100);
}
