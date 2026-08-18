# Pin Mapping and Wiring

## OLED

| OLED pin | ESP32 |
|---|---|
| VCC | 3.3 V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

## Ultrasonic sensors

| Slot | TRIG | ECHO | VCC | GND |
|---|---:|---:|---|---|
| 1 | 5 | 17 | 5 V | GND |
| 2 | 16 | 4 | 5 V | GND |
| 3 | 27 | 26 | 5 V | GND |
| 4 | 25 | 33 | 5 V | GND |

## LEDs

| Slot | Green | Red |
|---|---:|---:|
| 1 | 12 | 2 |
| 2 | 14 | 13 |
| 3 | 32 | 23 |
| 4 | 15 | 0* |

Each LED uses a 220 Ω series resistor.

`*` GPIO0 is selected for the virtual Wokwi diagram. Use a safer output GPIO for physical hardware.

## Buzzer

- Positive/control: GPIO 19
- Negative: GND

## Servo

- PWM/signal: GPIO 18
- V+: 5 V
- GND: common GND

## Physical safety

The virtual diagram is not a substitute for electrical protection. For physical ESP32 hardware, level-shift the HC-SR04 ECHO signal to an ESP32-safe voltage and provide a suitable supply/common ground for the servo and sensors.
