# System Architecture

## Block diagram

```text
+------------------+
| HC-SR04 Slot 1   |
+------------------+
          |
+------------------+
| HC-SR04 Slot 2   |
+------------------+
          |
+------------------+
| HC-SR04 Slot 3   |
+------------------+
          |
+------------------+
| HC-SR04 Slot 4   |
+------------------+
          |
          v
+---------------------------+
|          ESP32            |
| Read → Filter → Threshold |
| → Debounce → Count        |
+---------------------------+
     |      |      |     |
     v      v      v     v
   OLED    LEDs  Buzzer Servo
                    |
                    v
              Gate prototype

             |
             v
       Local Web Page
```

## Inputs

| Input | Meaning |
|---|---|
| S1 distance | Slot 1 distance |
| S2 distance | Slot 2 distance |
| S3 distance | Slot 3 distance |
| S4 distance | Slot 4 distance |

## Processing

1. Trigger one sensor.
2. Measure echo pulse duration.
3. Convert duration to centimetres.
4. Take five samples.
5. Remove minimum and maximum.
6. Average the remaining values.
7. Compare with 35 cm.
8. Apply 800 ms debounce.
9. Count occupied/free slots.
10. Update outputs.

## Outputs

- Green LED: slot free.
- Red LED: slot occupied.
- OLED: count and slot states.
- Buzzer: parking-full alert.
- Servo: gate demonstration.
- Serial Monitor: diagnostics.
- Web page: live status.
