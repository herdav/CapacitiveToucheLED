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
int sensitivityMAX = 200;
int sensitivityMIN = 0;
int setLEDtime = 100;
int hldLEDtime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  pinMode(pinTAS, INPUT);
  pinMode(pinREG, INPUT);
}

void loop() {
  bool stateTAS = digitalRead(pinTAS);
  int stateREG = analogRead(pinREG);
  int valREG = map(stateREG, 0, 1023, sensitivityMIN, sensitivityMAX);

  Serial.print(valREG);
  Serial.print("<");
  Serial.print(hldLEDtime);
  Serial.print(">");

  long measurement = sensor.capacitiveSensor(30);
  Serial.println(measurement);

  if (stateTAS || measurement > valREG || hldLED) {
    digitalWrite(pinLED, HIGH);
    hldLED = true;
  } else {
    digitalWrite(pinLED, LOW);
    hldLED = false;
  }
  if (hldLED) {
    hldLEDtime++;
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
