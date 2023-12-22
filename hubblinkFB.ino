#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "PLDTHOMEFIBRU6beg"
#define WIFI_PASSWORD "PLDTWIFI7vesa"
#define API_KEY "AIzaSyBVa4aKTIsutItMIuxbE7rtPN9O5MDRUkw"
#define DATABASE_URL "https://hubblink-9807b-default-rtdb.asia-southeast1.firebasedatabase.app/"

bool signupOk = false;
bool distanceState = true;
bool clapState = false;

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);
//Servo Motor
int servoPin = 18;  
Servo myServo;

// Ultrasonic Sensors
#define TRIG_PIN 23
#define ECHO_PIN 19
float duration_us, distance_cm;

FirebaseData fdbo_s1,fdbo_s2;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  myServo.attach(servoPin); 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd_i2c.init(); 
  lcd_i2c.backlight();

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.print(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
//Annoymuse
  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Signup OK");
    signupOk = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


  if(!Firebase.RTDB.beginStream(&fdbo_s1, "/Trash/Distance"))
      Serial.printf("Stream 1 begin error, %s\n\n", fdbo_s1.errorReason().c_str());
}

void loop() {
  if(Firebase.ready() && signupOk){

    // if(!Firebase.RTDB.readStream(&fdbo_s1))
    //   Serial.printf("Distance Mode Error %s\n\n", fdbo_s1.errorReason().c_str());

    //  if (fdbo_s1.streamAvailable()) {
    //         Serial.println("Success Dis.");
    //         delay(500);
    //         distanceState = fdbo_s1.boolData();
    //  }
    if (Firebase.RTDB.getBool(&fdbo_s1, "/Trash/Distance")) {
      if(fdbo_s1.dataType() == "boolean"){
            Serial.println("Success D.");
            delay(2000);
            distanceState = fdbo_s1.to<bool>();

              if(distanceState == true){
                  digitalWrite(TRIG_PIN, HIGH);
                  delayMicroseconds(10);
                  digitalWrite(TRIG_PIN, LOW);
                  duration_us = pulseIn(ECHO_PIN, HIGH);
                  distance_cm = 0.017 * duration_us;

                  Serial.print("distance: ");
                  Serial.println(distance_cm);

                  if(distance_cm < 20){
                    myServo.write(150); 
                  lcd_i2c.clear();
                  lcd_i2c.setCursor(0, 0);    
                  lcd_i2c.print("Trashcan: ");     
                  lcd_i2c.setCursor(2, 1);    
                  lcd_i2c.print("OPEN"); 
                  }
                  else{
                  myServo.write(0); 
                  lcd_i2c.clear(); 
                  lcd_i2c.setCursor(0, 0);      
                  lcd_i2c.print("Trashcan:");       
                  lcd_i2c.setCursor(2, 1);     
                  lcd_i2c.print("CLOSED"); 
                  }
}
      }
    } else {
      Serial.println("Failed: " + fdbo_s2.errorReason());
    }


    // if (Firebase.RTDB.getBool(&fdbo_s2, "/Trash/Clap")) {
    //   if(fdbo_s2.dataType() == "boolean"){
    //         Serial.println("Success Clap.");
    //         delay(2000);
    //         clapState = fdbo_s2.boolData();
    //   }
    // } else {
    //   Serial.println("Failed: " + fdbo_s2.errorReason());
    // }
    }// Signup   




  }//loop
