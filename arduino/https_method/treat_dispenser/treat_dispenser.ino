#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Stepper.h>
#include "pitches.h"
#include <ElegantOTA.h>

//// Setup LED
#define LED 22

// LED Functions
void blink()
{
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}

void rapid_blink()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }
}

//// Setup buzzer
#define BUZZER_PIN 23
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int durations[] = {4, 8, 8, 4, 4, 4, 4, 4};
int size = sizeof(durations) / sizeof(int);

void playMelody() {
  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

//// Setup webserver 
// Replace with your network credentials
const char *ssid = "SpyCats";
const char *password = "Felix&Jiji";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char *PARAM_INPUT_1 = "treats";
const char *PARAM_INPUT_2 = "jiggle";

// Variables to save values from HTML form
int steps;
bool treatRequest = false;
bool jiggleRequest = false;

// WiFi functions

void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    blink();
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void reconnectWiFi()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    blink();
    WiFi.begin(ssid, password);
  }
}

//// Setup stepper motor 
// Constants
const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
const int stepsPerDispense = 256;    // 8 pockets for treats makes an even 256 steps per distribution
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

//  Stepper functions
void dispenseTreat()
{
  myStepper.step(steps);
}

void jiggle()
{
  int j;
  for (int i = 0; i < 10; i++)
  {
    i % 2 == 0 ? j = -1 : j = 1;
    myStepper.step(j * 30);
    delay(100);
  }
}

//// Initialize LittleFS
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

//// Setup and Loop blocks
void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  initWiFi();
  initLittleFS();
  myStepper.setSpeed(5);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

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
  ElegantOTA.begin(&server);
}

void loop()
{
  // Verify that we are still connected to wifi
  if (WiFi.status() != WL_CONNECTED) {
    reconnectWiFi();
  }

  // Start ElegantOTA for remote updates
  ElegantOTA.loop();

  if (treatRequest)
  {
    rapid_blink();
    playMelody();
    dispenseTreat();
    treatRequest = false;
  }
  if (jiggleRequest)
  {
    rapid_blink();
    jiggle();
    jiggleRequest = false;
  }
}