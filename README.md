# capacitiveToucheLED
This setup detects a metal object of about 300g standing on a sensor plate of 100x150mm and turns on a led strip.

## Code
The script capacitiveToucheLED.ino use the modified [Capacitive Sensor Library](https://playground.arduino.cc/Main/CapacitiveSensor/) – see [Capacitive Touch Sensing with Nano Every](https://forum.arduino.cc/t/capacitive-touch-sensing-with-nano-every/1086407).

### Recalibration

The automatic recalibration must be turned off, otherwise the sensor will no longer detect the object after a certain period of time.

```ruby
const int AUTO_CALIBRATION_OFF = 0xFFFFFFFF;

void setup() {
  sensor.set_CS_AutocaL_Millis(AUTO_CALIBRATION_OFF);
}
```
The recalibration is triggered at specific times when:
```ruby
ledActive = false;
```

> [!NOTE]
> You can force the recalibration by touching the sensor with your hand for a few seconds.

## Sensor

The sensor consists of a postcard-sized cardboard about 1mm thick. On one side, the cardboard is glued to two equal halves (2 times 100 x 75 mm) with aluminum foil. Between the two halves is a gap of about 2 mm, the resistance is about 15 MΩ. One half is connected to the PCB via a cable. The aluminum foil can be painted or insulated with a material like paper or plasticfoil.
> [!NOTE]
> The maximum aluminum area directly connected to the PCB should not be larger than 75x100 mm. The cable (0.14mm²) length should not be longer than 40 cm.
> Do not cross the sensor cable with power cables.

## Circuit
![capacitiveTouchLED_circuit](https://github.com/herdav/capacitiveToucheLED/assets/19168117/01bdddb2-63c9-47bb-b205-9b79c3f7e3a5)

## PCB

> [!IMPORTANT]  
> It is important to connect the PCB to the ground, otherwise the sensor will not function properly.

![capacitiveTouchLED_pcb](https://github.com/herdav/capacitiveToucheLED/assets/19168117/e1b22fc1-3aec-4b77-82ad-2a3997d2a5f4)

