#include <ESP8266HTTPClient.h>
#include <WifiClient.h>
#include <setupConnection.h>

// #define RED_LED 9
// #define GREEN_LED 8

const char* ssid     = "AndroidAPc5c2";
const char* password = "routerpw";

String urlDB = "http://192.168.68.238:3000/tessera/";
WiFiClient wifiClient;
String macAddress = WiFi.macAddress();

void setup() {
  Serial.begin(9600);
  // pinMode(RED_LED, OUTPUT);
  // pinMode(GREEN_LED, OUTPUT);
  setupConnection(ssid, password);
}

void loop() {
  String idCard = readString(); // lettura tessera

  if(idCard != "") {
    blinkLed(idCard);
  }
}

bool checkID(String idCard, String url) {
    HTTPClient http;
    String urlFull = url + idCard + "-" + macAddress;
    http.begin(wifiClient, urlFull.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        http.end();
        return true;
    }

    http.end();
    return false;
}

void blinkLed(String idCard) {
    if(idCard) {
        if(checkID(idCard, urlDB)) {
            // digitalWrite(GREEN_LED, HIHG);
            // delay(2000);
            // digitalWrite(GREEN_LED, LOW);
            // simulazione led con stampa a seriale
            Serial.println("GREEN LED IS BLINKING!");
        }
        else {
            // digitalWrite(RED_LED, HIHG);
            // delay(2000);
            // digitalWrite(GREEN_LED, LOW);
            // simulazione led con stampa a seriale
            Serial.println("RED LED IS BLINKING");
        }
    }
}

String readString() {
  String str = "";
  String result = "";
  
  str = Serial.readString();

  if(str != "") {
    for(int i = 0; i < str.length() - 1; ++i) {
        result += str[i];
    }
  }

  return result;
}