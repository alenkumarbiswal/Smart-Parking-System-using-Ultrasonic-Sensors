# Wokwi Virtual Simulation Guide

## 1. Create the project

Use an ESP32 DevKit C project in Wokwi.

## 2. Add the circuit

Copy `simulation/diagram.json` into the project's diagram.

The diagram contains:

- ESP32 DevKit C
- 4 × HC-SR04
- SSD1306 OLED
- 8 × LEDs
- 8 × 220 Ω resistors
- buzzer
- servo

## 3. Add the sketch

Copy `arduino_code/smart_parking.ino` into the Wokwi sketch.

## 4. Libraries

Install:

- Adafruit GFX Library
- Adafruit SSD1306

## 5. Run

Start simulation and open Serial Monitor at 115200 baud.

## 6. Change sensor distances

Click an HC-SR04 and change its distance.

Suggested values:

- 100 cm = FREE
- 10–30 cm = OCCUPIED

The threshold is 35 cm.

## 7. Verify outputs

When a slot becomes occupied:

- Green LED turns OFF.
- Red LED turns ON.
- OLED changes from FREE to OCCUPIED.
- Available count decreases.

When all four are occupied:

- OLED displays PARKING FULL.
- All red LEDs are ON.
- Buzzer beeps.
- Servo is held closed.

When a slot becomes free again:

- Available count increases.
- The full condition clears.
- The servo may run its availability demonstration cycle.
