# capacitiveToucheLED

This setup detects a metal object of about 300g standing on a sensor plate of 100x150mm and turns on a led strip.

## Code
The script capacitiveToucheLED.ino use the [Capacitive Sensor Library](https://playground.arduino.cc/Main/CapacitiveSensor/).

### Re-calibration

The Re-calibration must be turned off, otherwise the sensor will no longer detect the object after a certain period of time.

```ruby
const int AUTO_CALIBRATION_OFF = 0xFFFFFFFF;

void setup() {
  sensor.set_CS_AutocaL_Millis(AUTO_CALIBRATION_OFF);
}
```

## Sensor

The sensor consists of a postcard-sized cardboard about 1mm thick. On one side, the cardboard is glued to two equal halves (2 times 100 x 75 mm) with aluminum foil. Between the two halves is a gap of about 2 mm, the resistance is about 15 MΩ. One half is connected to the PCB via a cable. The aluminum foil can be painted or insulated with a material like paper or plasticfoil.
> [!NOTE]
> The maximum aluminum area directly connected to the PCB should not be larger than 75x100 mm. The cable length (0.14mm²) should not be longer than 40 cm.

## Circuit

> [!IMPORTANT]  
> It is important to connect the circuit board to the ground, otherwise the sensor will not function properly.

![capacitiveTouchLED_circuit](https://github.com/herdav/capacitiveToucheLED/assets/19168117/c0dfe580-47c4-4416-99e9-67c8fdf2b39f)

## PCB

![capacitiveTouchLED_pcb](https://github.com/herdav/capacitiveToucheLED/assets/19168117/cb148621-ec05-4953-81a8-7040029f4bcb)

