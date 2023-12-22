#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "DevLin"
#define WIFI_PASSWORD "Wangsulong@2021"
#define API_KEY "AIzaSyBpENWj2_UR9MsKNy9ftje3sASi5jVPd6c"
#define DATABASE_URL "https://arduino-cd6b8-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define Led_Pin_1 23
#define Led_Pin_2 21
#define LDR_Pin 34
#define Tactile_Switch_Pin 12
#define PMWChannel 0

const int freq = 50000;
const int resol = 8;


FirebaseData fbdo, fdbo_s1, fdbo_s2;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOk = false;
int ldrData = 0; 
float volt = 0.0;
int pwmValue = 0;
bool ledstat = false;
bool tactileSwitchState = false;

void setup() {
 
 pinMode(Led_Pin_2, OUTPUT);
 ledcSetup(PMWChannel, freq, resol);
 ledcAttachPin(Led_Pin_1, PMWChannel);
  pinMode(Tactile_Switch_Pin, INPUT_PULLUP);
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

  //Stream
  if(!Firebase.RTDB.beginStream(&fdbo_s1, "/Led/analog"))
      Serial.printf("Stream 1 begin error, %s\n\n", fdbo_s1.errorReason().c_str());
  if(!Firebase.RTDB.beginStream(&fdbo_s2, "/Led/digital"))
      Serial.printf("Stream 1 begin error, %s\n\n", fdbo_s2.errorReason().c_str());
}

void loop() {

 tactileSwitchState = digitalRead(Tactile_Switch_Pin) == LOW;

  if(Firebase.ready() && signupOk && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)){
    // Store sensor data.
    sendDataPrevMillis = millis();
    ldrData = analogRead(LDR_Pin);
    volt = (float)analogReadMilliVolts(LDR_Pin) / 10000;

    if(Firebase.RTDB.setInt(&fbdo, "Sensor/ldrData", ldrData)){
      Serial.println(ldrData);
      Serial.print("Successfully saved to: ");
      Serial.print(fbdo.dataPath());
      Serial.print(" | " + fbdo.dataType() );

    }
    
    else{
      Serial.println("Failed: " + fbdo.errorReason());
    }

    if(Firebase.RTDB.setFloat(&fbdo, "Sensor/voltage", volt)){
      Serial.println(volt);
      Serial.print("Successfully saved to: ");
      Serial.print(fbdo.dataPath());
      Serial.print(" | " + fbdo.dataType() );

    }
    else{
      Serial.println("Failed: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setBool(&fbdo, "Sensor/switch", tactileSwitchState)) {
      Serial.println(tactileSwitchState ? "Tactile switch not pushed" : "Tactile switch  pushed");
      Serial.print("Successfully saved to: ");
      Serial.print(fbdo.dataPath());
      Serial.print(" | " + fbdo.dataType());
    } else {
      Serial.println("Failed: " + fbdo.errorReason());
    }
} // Millis

if(Firebase.ready() && signupOk){

if(!Firebase.RTDB.readStream(&fdbo_s1))
   Serial.printf("Stream 1 begin error, %s\n\n", fdbo_s1.errorReason().c_str());

if (fdbo_s1.streamAvailable()) {
      float voltageValue = fbdo_s1.floatData();
      if (voltageValue >= 0.0 && voltageValue <= 3.0) {
        pwmValue = (int)(voltageValue * 4095 / 3.0);
        Serial.println("Successful READ from " + fbdo_s1.dataPath() +
                      " : " + voltageValue + "V (" + fbdo_s1.dataType() + ")");
        ledcWrite(PMWChannel, pwmValue);
      } else {
        Serial.println("Voltage value out of range (0.0-3.0)");
      }
    } 

  if(!Firebase.RTDB.readStream(&fdbo_s2))
   Serial.printf("Stream 2 begin error, %s\n\n", fdbo_s2.errorReason().c_str());

   
  } // Loop