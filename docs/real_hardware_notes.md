# Real Hardware Notes

This repository is currently optimized for virtual simulation.

Before building the physical prototype:

1. Replace GPIO0 used by Slot 4 red LED with a safe output GPIO.
2. Level-shift HC-SR04 ECHO signals to an ESP32-safe voltage.
3. Use a suitable supply for the servo and ultrasonic sensors.
4. Keep all grounds common.
5. Use 220 Ω series resistors for LEDs.
6. Mount sensors consistently and calibrate the threshold.
7. Keep ultrasonic sensors spatially separated or trigger them sequentially to reduce cross-talk.
8. Do not use a USB/5 V rail beyond its current capability for a servo without checking the supply requirements.
