#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

unsigned long delayTime;

// Replace with your network details
const char* ssid = "yes, we scan!";
const char* password = "Christine2016";

void setup() {
  Serial.begin(115200);
  delay(10);
  Wire.begin(D3, D4);
  Wire.setClock(100000);
  Serial.println(F("BME280 test"));

  bool status;

  // default settings
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();

  delay(100); // let sensor boot up

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
  Serial.println(F("BME280 test"));
}

void loop() {
  printHTTP();
  delay(delayTime);
}

void printHTTP() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient

    String httppost = "http://192.168.0.201/wetter.php?page=edit&temp="
                      + String(bme.readTemperature())
                      + "&press=" + String(bme.readPressure())
                      + "&humi=" + String(bme.readHumidity())
                      + "&alti=" + String(bme.readAltitude(SEALEVELPRESSURE_HPA));

    http.begin(httppost);     //Specify request destination

    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    int httpCode = http.POST("Message from ESP8266");   //Send the request
    String payload = http.getString();                  //Get the response payload
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }
}

