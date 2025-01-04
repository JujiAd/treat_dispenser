#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
const int stepsPerDispense = 256;    // 8 pockets for treats makes an even 256 steps per distribution
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
#define LED 2
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Replace with your network credentials
const char *ssid = "wifi_name";
const char *password = "wifi_password";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char *PARAM_INPUT_1 = "treats";
const char *PARAM_INPUT_2 = "jiggle";

// Variables to save values from HTML form
int steps;
bool treatRequest = false;
bool jiggleRequest = false;

// Initialize LittleFS
void initLittleFS()
{
  if (!LittleFS.begin(true))
  {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else
  {
    Serial.println("LittleFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  initWiFi();
  initLittleFS();
  myStepper.setSpeed(5);
  pinMode(LED, OUTPUT);

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  server.serveStatic("/", LittleFS, "/");

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    int params = request->params();
    Serial.print("Number of input params: ");
    Serial.println(String(params));

    for(int i=0;i<params;i++){
      const AsyncWebParameter* p = request->getParam(i);
      Serial.printf("Parameter: %s, %s\n", p->name().c_str(), p->value().c_str());

      // HTTP POST treat request
      if (p->name() == PARAM_INPUT_1 && p->value().toInt() != 0) {
        int treats = p->value().toInt();
        steps = stepsPerDispense * treats;
        treatRequest = true;
      }
      // HTTP POST jiggle request
      if (p->name() == PARAM_INPUT_2 && p->value()) {
        steps = 0;
        jiggleRequest = true;
      }
    }
    request->send(LittleFS, "/index.html", "text/html"); });

  server.begin();
}

void dispenseTreat()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  digitalWrite(LED, HIGH);
  myStepper.step(steps);
  delay(1000);
  digitalWrite(LED, LOW);
}

void jiggle()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }
  int j;
  for (int i = 0; i < 10; i++)
  {
    i % 2 == 0 ? j = -1 : j = 1;
    myStepper.step(j * 30);
    delay(100);
  }
}

void loop()
{
  if (treatRequest)
  {
    dispenseTreat();
    treatRequest = false;
  }
  if (jiggleRequest)
  {
    jiggle();
    jiggleRequest = false;
  }
}