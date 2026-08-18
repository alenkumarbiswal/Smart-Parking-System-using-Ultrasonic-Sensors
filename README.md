# Smart Parking System using Ultrasonic Sensors

An ESP32-based embedded smart parking prototype that monitors four parking slots using HC-SR04 ultrasonic sensors, shows availability on an SSD1306 OLED, provides red/green slot indicators, activates a buzzer when parking is full, and demonstrates an entry barrier using a servo.

## Project status

- Target: Virtual simulation in Wokwi
- Controller: ESP32 DevKit C
- Parking slots: 4
- Slot sensor: HC-SR04 × 4
- Display: SSD1306 128×64 I2C OLED
- Indicators: 2 LEDs per slot
- Alert: buzzer
- Gate prototype: servo
- Web status page: ESP32 local web server
- Occupancy threshold: 35 cm
- Filtering: 5 readings with min/max trimming
- State debounce: 800 ms

## Features

1. Real-time FREE/OCCUPIED detection for four slots.
2. Available-slot counting.
3. Green LED for FREE and red LED for OCCUPIED.
4. OLED status display.
5. PARKING FULL message and buzzer alert.
6. Servo barrier demonstration: open when a slot is available; closed when full.
7. Serial Monitor diagnostics.
8. Local ESP32 web page with automatic refresh.

## System flow

```text
Parking Slot
     ↓
HC-SR04 Ultrasonic Sensor
     ↓
Distance Measurement
     ↓
ESP32
     ↓
Threshold + Filtering + Debounce
     ↓
FREE / OCCUPIED
     ↓
Available Slot Count
     ↓
OLED + LEDs + Buzzer + Servo + Web Page
```

## Repository structure

```text
Smart-Parking-Ultrasonic-Embedded-System/
├── src/
├── arduino_code/
│   └── smart_parking.ino
├── simulation/
│   ├── diagram.json
│   ├── libraries.txt
│   └── wokwi.toml
├── circuit_diagram/
│   ├── circuit_connections.md
│   └── pin_mapping.svg
├── data/
│   ├── test_matrix.csv
│   └── sample_measurements.csv
├── test_cases/
│   ├── test_results.md
│   └── test_execution_sheet.md
├── outputs/
│   ├── sample_serial_monitor.txt
│   └── sample_oled_output.txt
├── screenshots/
│   ├── 01_initial_circuit.png
│   ├── 02_empty_parking.png
│   ├── ...
│   └── 13_final_simulation.png
├── reports/
│   ├── Smart_Parking_Project_Report.pdf
│   ├── Smart_Parking_Testing_Report.pdf
│   └── Smart_Parking_Circuit_Design.pdf
├── docs/
│   ├── project_overview.md
│   ├── architecture.md
│   ├── pin_mapping.md
│   ├── implementation_plan.md
│   ├── simulation_guide.md
│   ├── testing_strategy.md
│   ├── troubleshooting.md
│   ├── github_upload.md
│   └── interview_questions.md
├── README.md
└── .gitignore
```

## Pin configuration

| Function | GPIO |
|---|---:|
| OLED SDA | 21 |
| OLED SCL | 22 |
| Servo PWM | 18 |
| Buzzer | 19 |
| Slot 1 TRIG | 5 |
| Slot 1 ECHO | 17 |
| Slot 2 TRIG | 16 |
| Slot 2 ECHO | 4 |
| Slot 3 TRIG | 27 |
| Slot 3 ECHO | 26 |
| Slot 4 TRIG | 25 |
| Slot 4 ECHO | 33 |
| Slot 1 Green / Red | 12 / 2 |
| Slot 2 Green / Red | 14 / 13 |
| Slot 3 Green / Red | 32 / 23 |
| Slot 4 Green / Red | 15 / 0 |

GPIO0 is used for Slot 4 red LED only in the virtual simulation. For physical hardware, choose a safer output GPIO and update both `diagram.json` and the sketch.

## Distance logic

The HC-SR04 measures echo travel time. The standard relationship is:

```text
Distance = (Echo Time × Speed of Sound) / 2
```

The division by two accounts for the outgoing and returning sound path.

For this prototype:

```text
Average distance < 35 cm  → OCCUPIED
Average distance ≥ 35 cm  → FREE
```

Five readings are taken and the highest and lowest values are discarded before averaging.

## How to run in Wokwi

1. Open a Wokwi ESP32 project.
2. Replace the circuit with `simulation/diagram.json`.
3. Use `arduino_code/smart_parking.ino` as the sketch.
4. Install the libraries listed in `simulation/libraries.txt`.
5. Start the simulation.
6. Open Serial Monitor at 115200 baud.
7. Click each HC-SR04 and change its distance.
8. Test the cases in `test_cases/test_execution_sheet.md`.
9. Capture the required evidence in `screenshots/`.

## Test sequence

| Test | S1 | S2 | S3 | S4 | Expected free |
|---|---:|---:|---:|---:|---:|
| TC01 All free | 100 | 100 | 100 | 100 | 4 |
| TC02 Slot 1 occupied | 10 | 100 | 100 | 100 | 3 |
| TC03 Two occupied | 10 | 15 | 100 | 100 | 2 |
| TC04 Three occupied | 10 | 15 | 20 | 100 | 1 |
| TC05 Full | 10 | 15 | 20 | 12 | 0 |
| TC06 Vehicle departure | 10 | 100 | 20 | 12 | 1 |

## Required evidence

Capture:

1. Project folder structure.
2. Complete circuit.
3. All slots free.
4. Slot 1 occupied.
5. Two slots occupied.
6. Three slots occupied.
7. Parking full.
8. Green LED indication.
9. Red LED indication.
10. OLED available-slot count.
11. Buzzer alert.
12. Servo gate.
13. Serial Monitor.
14. Test results.
15. Final simulation.
16. GitHub repository and README.

Do not invent screenshots or mark a test PASS until it has actually been observed in Wokwi.

## Important virtual-simulation note

The diagram intentionally connects the HC-SR04 modules directly to the ESP32 for simulation convenience. For real hardware, HC-SR04 ECHO is commonly a 5 V signal; use appropriate level shifting/voltage division before connecting it to ESP32 GPIO.

## Author

**Alen Kumar Biswal**

B.Tech Computer Science & Engineering  
Embedded Systems / UI/UX / Frontend Development
