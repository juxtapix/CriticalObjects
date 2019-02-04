/*
  Get Data - txt

  created 1 Nov 2018
  by Pedro Oliveira
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<SSID>";
const char* password = "<PASS>";

const String endpoint = "https://eloquentjavascript.net/1st_edition/files/";
const String key = "fruit.txt";
String payload;

String getData() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;
    http.begin(endpoint + key);         //Specify the URL
    int httpCode = http.GET();          //Make the request

    if (httpCode > 0) {                 //Check for the returning code
      payload = http.getString();

      return payload;

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

  Serial.println(getData());

  //disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {

}
