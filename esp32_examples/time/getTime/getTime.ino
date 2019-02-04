/*
  Get Formatted Time
  (Modified "SimpleTime" Example)

  created 1 Nov 2018
  by Pedro Oliveira

  -

  %a Abbreviated weekday name
  %A Full weekday name
  %b Abbreviated month name
  %B Full month name
  %c Date and time representation for your locale
  %d Day of month as a decimal number (01-31)
  %H Hour in 24-hour format (00-23)
  %I Hour in 12-hour format (01-12)
  %j Day of year as decimal number (001-366)
  %m Month as decimal number (01-12)
  %M Minute as decimal number (00-59)
  %p Current locale's A.M./P.M. indicator for 12-hour clock
  %S Second as decimal number (00-59)
  %U Week of year as decimal number,  Sunday as first day of week (00-51)
  %w Weekday as decimal number (0-6; Sunday is 0)
  %W Week of year as decimal number, Monday as first day of week (00-51)
  %x Date representation for current locale
  %X Time representation for current locale
  %y Year without century, as decimal number (00-99)
  %Y Year with century, as decimal number
*/

#include <WiFi.h>
#include "time.h"

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -4 * 3600;   // NYC: GMT-4
const int   daylightOffset_sec = 3600;

String getTime(const char* timeformat)
{
  struct tm timeinfo;
  char timeStringBuff[80];
  if(!getLocalTime(&timeinfo)){
    return "Failed to get time";
  }
  strftime(timeStringBuff, sizeof(timeStringBuff), timeformat, &timeinfo);
  return timeStringBuff;
}

void setup()
{
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" Connected");

  //init and get time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println(getTime("%A, %B %d %Y %H:%M:%S"));

  //disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  Serial.println( getTime("%A, %B %d %Y %H:%M:%S") );
  Serial.println( getTime("%S").toInt() );
  Serial.println( getTime("%S").toInt() + 10);
}
