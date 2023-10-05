# capacitiveToucheLED

## Code
The script capacitiveToucheLED.ino use the [Capacitive Sensor Library](https://playground.arduino.cc/Main/CapacitiveSensor/).

### Re-calibration must be turned off

```ruby
const int AUTO_CALIBRATION_OFF = 0xFFFFFFFF;

void setup() {
  sensor.set_CS_AutocaL_Millis(AUTO_CALIBRATION_OFF);
}
```

## Circuit

> [!IMPORTANT]  
> It is important to connect the circuit board to the ground.


![capacitiveTouchLED_circuit](https://github.com/herdav/capacitiveToucheLED/assets/19168117/c0dfe580-47c4-4416-99e9-67c8fdf2b39f)
