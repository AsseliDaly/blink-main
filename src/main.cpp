#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>
#define WIFI_SSID "Orange-206F"
#define WIFI_PASSWORD "RM66H5AA151"
#define API_KEY "hiKFiRYaKpcQ62CjhXfqmJSX9XoZKBoGk7AA3oUf"

/* 2. Define the RTDB URL */
#define DATABASE_URL "https://sbapp-6c7c9-default-rtdb.firebaseio.com"
#define LED_BUILTIN 2

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String stringVal ="";

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
    Serial.println();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

    /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  

    
  

   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getString(&fbdo, "/state")) {
      
        stringVal = fbdo.stringData();
        Serial.println(stringVal);
        if(stringVal=="on"){ digitalWrite(LED_BUILTIN ,HIGH);}
        else if(stringVal=="off"){ digitalWrite(LED_BUILTIN ,LOW);}
        Serial.println(fbdo.stringData());
           
        
    }







  
}
}