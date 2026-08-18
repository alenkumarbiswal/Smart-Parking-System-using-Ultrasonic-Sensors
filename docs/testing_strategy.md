# Testing and Calibration Strategy

## Test procedure

1. Start the simulation.
2. Set all four sensors to 100 cm.
3. Verify all slots are FREE.
4. Change S1 to 10 cm.
5. Verify S1 is OCCUPIED.
6. Change S2 and S3 to occupied distances.
7. Verify the count decreases.
8. Set all four sensors below 35 cm.
9. Verify PARKING FULL and buzzer.
10. Free one sensor.
11. Verify count recovery and alert clearing.
12. Record screenshots.

## Test cases

See `test_cases/test_execution_sheet.md`.

## Calibration

Start with 35 cm. The source project recommends adjusting the threshold by approximately ±5 cm if required by sensor mounting and verifying jitter using averaged readings.

## Noise and invalid readings

The implementation takes five readings, removes the minimum and maximum, and averages the remaining three. `pulseIn()` timeout is treated as an invalid/no-echo reading represented by a very large distance.

## Evidence rule

Only mark PASS after the actual behavior is observed. Record actual output and screenshot filename.
