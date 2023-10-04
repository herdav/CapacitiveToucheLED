// CAPACITIVE TOUCH LED
// Created 2023 by David Herren
// https://davidherren.ch
// https://github.com/herdav/capacitiveTouchLED
// --------------------------------------

#include <CapacitiveSensor.h>

#define pinTAS 10   // Taster pin
#define pinLED 8    // LED pin
#define pinREG A0   // Sensitivity control pin

CapacitiveSensor sensor = CapacitiveSensor(4, 2); // 1M resistor between pins 4 & 2, pin 2 is sensor pin

bool hldLED = false;
bool hldDLY = false;
int sensitivityMAX = 200;
int sensitivityMIN = 0;
int setLEDtime = 100;
int hldLEDtime = 0;
int setDLYtime = 50;
int hldDLYtime = 0;
String isRun = "OFF";

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  pinMode(pinTAS, INPUT);
  pinMode(pinREG, INPUT);

  sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibration
}

void loop() {
  bool stateTAS = digitalRead(pinTAS);
  int stateREG = analogRead(pinREG);
  int valREG = map(stateREG, 0, 1023, sensitivityMIN, sensitivityMAX);

  Serial.print(isRun);
  Serial.print(valREG);
  Serial.print("<");
  Serial.print(hldDLYtime);
  Serial.print("_");
  Serial.print(hldLEDtime);
  Serial.print(">");

  long measurement = sensor.capacitiveSensor(30);
  Serial.println(measurement);

  if (stateTAS || measurement > valREG || hldLED) {
    hldDLYtime++;
    if (hldDLYtime >= setDLYtime || hldDLY) {
      hldDLY = true;
      digitalWrite(pinLED, HIGH);
      hldLED = true;
      isRun = "ON--";
    }
  } else {
    digitalWrite(pinLED, LOW);
    hldLED = false;
    isRun = "OFF-";
    hldDLY = false;
    hldDLYtime = 0;
  }
  if (hldLED) {
    hldLEDtime++;
    hldDLYtime = 0;
    if (hldLEDtime >= setLEDtime) {
      hldLED = false;
      hldLEDtime = 0;
    }
    if (stateTAS || measurement > valREG) {
      hldLEDtime = 0;
    }
  }
  delay(10);
}
