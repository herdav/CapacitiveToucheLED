// CAPACITIVE TOUCH LED
// Created 2023 by David Herren
// https://davidherren.ch
// https://github.com/herdav/capacitiveTouchLED
// --------------------------------------

#include <CapacitiveSensor.h>

#define PIN_TAS 10 // Taster pin
#define PIN_LED 8  // LED pin
#define PIN_REG A0 // Sensitivity control pin (40/200)

CapacitiveSensor sensor = CapacitiveSensor(4, 2); // 1M resistor between pins 4 & 2, pin 2 is sensor pin
const int AUTO_CALIBRATION_OFF = 0xFFFFFFFF;

bool ledActive = false;
bool delayActive = false;
int sensitivityMAX = 200;
int setLEDtime = 100;
int ledOnTime = 0;
int setDelayTime = 50;
int delayTime = 0;
String ledStatus = "OFF";

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TAS, INPUT);
  pinMode(PIN_REG, INPUT);

  sensor.set_CS_AutocaL_Millis(AUTO_CALIBRATION_OFF);
}

void loop() {
  bool buttonState = digitalRead(PIN_TAS);
  int sensitivityValue = map(analogRead(PIN_REG), 0, 1023, 0, sensitivityMAX);
  long measurement = sensor.capacitiveSensor(30);

  Serial.print(ledStatus);
  Serial.print(sensitivityValue);
  Serial.print("<");
  Serial.print(delayTime);
  Serial.print("_");
  Serial.print(ledOnTime);
  Serial.print(">");
  Serial.println(measurement);

  if (buttonState || measurement > sensitivityValue || ledActive) {
    delayTime++;
    if (delayTime >= setDelayTime || delayActive) {
      delayActive = true;
      digitalWrite(PIN_LED, HIGH);
      ledActive = true;
      ledStatus = "ON--";
    }
  } else {
    resetLED();
  }

  if (ledActive) {
    ledOnTime++;
    delayTime = 0;
    if (ledOnTime >= setLEDtime) {
      resetLED();
    }
    if (buttonState || measurement > sensitivityValue) {
      ledOnTime = 0;
    }
  }
  delay(10);
}

void resetLED() {
  digitalWrite(PIN_LED, LOW);
  ledActive = false;
  ledStatus = "OFF-";
  delayActive = false;
  delayTime = 0;
  ledOnTime = 0;
}
