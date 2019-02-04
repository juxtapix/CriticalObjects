/*
  Get Data - xml

  created 1 Nov 2018
  by Pedro Oliveira
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

const String endpoint = "https://eloquentjavascript.net/1st_edition/files/";
const String key = "fruit.xml";
String payload;

struct f{
  String name;
  String color;
};
struct f fruit[2];

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

  xmlParse(getData());

  //Print parsed xml
  Serial.println(fruit[0].name);
  Serial.println(fruit[0].color);
  Serial.println(fruit[1].name);
  Serial.println(fruit[1].color);
  Serial.println(fruit[2].name);
  Serial.println(fruit[2].color);

  //disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {

}

void xmlParse(String payload) {
  String parentTag = "<fruit>";
  const char *sub = const_cast<char*>(parentTag.c_str());
  const char *str = const_cast<char*>(payload.c_str());
  int length = strlen(sub);
  int count = 0;
  for (str = strstr(str, sub); str; str = strstr(str + length, sub)) {
    String select = String(str);
    fruit[count].name = select.substring(select.indexOf("<name>") + 6, select.indexOf("</name>"));
    fruit[count].color = select.substring(select.indexOf("<color>") + 7, select.indexOf("</color>"));
    ++count;
  }
}
