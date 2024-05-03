#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// #define ANALOG_PIN 35

const char* ssid = "ESP32AP";
const char* password = "Password";
const char* receiver_ip("192.168.4.1");
const int joyx = 34;
const int joyy = 33;
const int joyb = 21;
int xval=0;
int yval=0;
int button=1;
int angle=0;
int check_connection=0;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  // Create Wi-Fi network 
  Serial.println("Starting Access Point");
  WiFi.softAP(ssid, password);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
  Serial.println("WiFi server started");

  // Define pinMode
  pinMode(joyx, INPUT);
  pinMode(joyy, INPUT);
  pinMode(joyb, INPUT_PULLUP);
}

void loop() {
  // Check for client connections
  WiFiClient client = server.available();
  if (check_connection=0 && client)
  {
    Serial.println("New client connected");
    int check_connection=1;
  }

  xval = analogRead(joyx);
  yval = analogRead(joyy);
  button = digitalRead(joyb);

  if (client) {

    // Read request 
    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);

    // Send response
    String xstringval = String(xval);
    String ystringval = String(yval);
    String buttonval = String(button);
    client.print("xval= "+xstringval+" ");
    client.print("yval= "+ystringval+" ");
    client.print("buttonval= "+buttonval+" ");
    client.flush();
    // Serial.println(xstringval);
    // Serial.println(ystringval);
    // Serial.println(buttonval);
  }

}