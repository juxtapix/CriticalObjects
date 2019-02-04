/*
  Get Data - json

  created 1 Nov 2018
  by Pedro Oliveira
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

const String endpoint = "http://arduinojson.org/";
const String key = "example.json";
String payload;

// Allocate JsonBuffer
// Use arduinojson.org/assistant to compute the capacity.
const size_t capacity = JSON_OBJECT_SIZE(9) + 250;
DynamicJsonBuffer jsonBuffer(capacity);

JsonObject& getData() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;
    http.begin(endpoint + key);         //Specify the URL
    int httpCode = http.GET();          //Make the request

    if (httpCode > 0) {                 //Check for the returning code
      payload = http.getString();
      // Parse JSON object
      JsonObject& root = jsonBuffer.parseObject(payload);
      if (!root.success()) {
        Serial.println(F("Parsing failed!"));
        //        return;
      }
      return root;
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
}

void setup() {
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // Get and parse data
  Serial.println(getData()["sensor"].as<char*>());
  Serial.println(getData()["time"].as<char*>());
  Serial.println(getData()["data"][0].as<char*>());
  Serial.println(getData()["data"][1].as<char*>());

  //disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {

}
