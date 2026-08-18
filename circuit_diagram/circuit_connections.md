# Circuit Connections

## Complete connection table

| Component | Pin | ESP32 / Common |
|---|---|---|
| OLED | SDA | GPIO21 |
| OLED | SCL | GPIO22 |
| OLED | VCC | 3V3 |
| OLED | GND | GND |
| HC-SR04 S1 | TRIG | GPIO5 |
| HC-SR04 S1 | ECHO | GPIO17 |
| HC-SR04 S2 | TRIG | GPIO16 |
| HC-SR04 S2 | ECHO | GPIO4 |
| HC-SR04 S3 | TRIG | GPIO27 |
| HC-SR04 S3 | ECHO | GPIO26 |
| HC-SR04 S4 | TRIG | GPIO25 |
| HC-SR04 S4 | ECHO | GPIO33 |
| Buzzer | Signal | GPIO19 |
| Servo | PWM | GPIO18 |
| Servo | V+ | 5V |
| Servo | GND | GND |

### Slot LEDs

Each LED is connected through a 220 Ω resistor.

| Slot | Green LED | Red LED |
|---|---|---|
| 1 | GPIO12 → R1 → LED5 | GPIO2 → R? → LED1 |
| 2 | GPIO14 → R6 → LED6 | GPIO13 → R2 → LED2 |
| 3 | GPIO32 → R7 → LED7 | GPIO23 → R3 → LED3 |
| 4 | GPIO15 → R8 → LED8 | GPIO0 → R4 → LED4 |

## Wokwi-specific note

The supplied `diagram.json` directly connects HC-SR04 ECHO to ESP32 GPIO for simulation. In physical hardware, use voltage-level protection for ECHO.

## Visual architecture

```text
S1 HC-SR04 ─┐
S2 HC-SR04 ─┤
S3 HC-SR04 ─┼──> ESP32 ──> OLED
S4 HC-SR04 ─┘       │ ├──> Green/Red LEDs
                    │ ├──> Buzzer
                    │ ├──> Servo
                    │ └──> Web page
```
