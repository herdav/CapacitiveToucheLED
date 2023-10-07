// capacitiveToucheLED
// Version 231007
// Created 2023 by David Herren
// https://davidherren.ch
// https://github.com/herdav/capacitiveTouchLED
// --------------------------------------------

#include <CapacitiveSensor.h>

#define PIN_TAS 10 // Taster pin.
#define PIN_LED 8  // LED pin.
#define PIN_REG A0 // Sensitivity control pin (50/100).

CapacitiveSensor sensor = CapacitiveSensor(4, 2); // 1M resistor between pins 4 & 2, pin 2 is sensor pin.
const int AUTO_CALIBRATION_OFF = 0xFFFFFFFF;

bool ledActive = false;
bool delayActive = false;
bool buttonState = false;
long measurement;
int setSensitivityMax = 100;
int sensitivityValue; // 40
int setLEDtime = 50; // 100
int countLedOnTime = 0;
int countLedActiveTime = 0;
int setDelayTime = 50; // 50
int countDelayTime = 0;
int countWaitingTime = 0; // Counts time while sensor is inactive.
int setResetTime = 100; // Reset sensor after setResetTime.
int setHandToucheValue = 500; // Sensor value when hand touched.
int countHandTouche = 0; // Counts the time where hand touches.
int setHandToucheTime = 50; // Set value when trigger when hand touched.
String ledStatus = "OFF";

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TAS, INPUT);
  pinMode(PIN_REG, INPUT);

  sensor.set_CS_AutocaL_Millis(AUTO_CALIBRATION_OFF);
}

void loop() {
  buttonState = digitalRead(PIN_TAS);
  sensitivityValue = map(analogRead(PIN_REG), 0, 1023, 0, setSensitivityMax);
  measurement = sensor.capacitiveSensor(30);

  Serial.print(ledStatus);
  Serial.print(countWaitingTime);
  Serial.print("-");
  Serial.print(sensitivityValue);
  Serial.print("<");
  Serial.print(countDelayTime);
  Serial.print("_");
  Serial.print(countLedOnTime);
  Serial.print(">");
  Serial.println(measurement);

  if (buttonState || measurement > sensitivityValue || ledActive) {
    countDelayTime++;
    if (countDelayTime >= setDelayTime || delayActive) {
      delayActive = true;
      digitalWrite(PIN_LED, HIGH);
      ledActive = true;
      ledStatus = "ON--";
    }
  } else { resetLED(); }

  if (ledActive) {
    countLedOnTime++;
    countDelayTime = 0;
    if (countLedOnTime >= setLEDtime) { resetLED(); }
    if (buttonState || measurement > sensitivityValue) { countLedOnTime = 0; }
  }

  if ((measurement < sensitivityValue) && !ledActive) { // Reset sensor after setResetTime.
    countWaitingTime++;
    if (countWaitingTime >= setResetTime) {
      sensor.reset_CS_AutoCal();
      Serial.println(">>> RESETED <<<");
      countWaitingTime = 0;
      delay(500);
    }
  } else { countWaitingTime = 0; }

  if (ledActive) { 
    countLedActiveTime++;
    if (measurement > setHandToucheValue) {
      countHandTouche++;
      Serial.println(countHandTouche);
      if (countHandTouche >= setHandToucheTime) {
        sensor.reset_CS_AutoCal();
        countHandTouche = 0;
      }
    }
  }
  delay(10);
}

void resetLED() {
  digitalWrite(PIN_LED, LOW);
  ledActive = false;
  ledStatus = "OFF-";
  delayActive = false;
  countDelayTime = 0;
  countLedOnTime = 0;
}
