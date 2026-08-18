# Testing and Validation

## Test Matrix

| Test ID | Input / Condition | Expected Output | Actual Output | Result |
|---|---|---|---|---|
| TC-01 | Bright room + no motion | Light OFF | Record during test | PASS/FAIL |
| TC-02 | Dark room + motion | Light ON | Record during test | PASS/FAIL |
| TC-03 | Temperature ≥ 30 °C | Fan ON | Record during test | PASS/FAIL |
| TC-04 | Temperature ≤ 28 °C | Fan OFF | Record during test | PASS/FAIL |
| TC-05 | Security armed + motion | Red LED + buzzer + INTRUDER ALERT | Record during test | PASS/FAIL |
| TC-06 | Security armed + no motion | Alarm OFF | Record during test | PASS/FAIL |
| TC-07 | Light button | Manual light toggle | Record during test | PASS/FAIL |
| TC-08 | Fan button | Manual fan toggle | Record during test | PASS/FAIL |
| TC-09 | Long light-button press | Light AUTO mode | Record during test | PASS/FAIL |
| TC-10 | Long fan-button press | Fan AUTO mode | Record during test | PASS/FAIL |

## Evidence Requirements

For each test, capture the simulator state and, where useful, the Serial Monitor/OLED at the same time.

### Priority screenshots

1. Complete circuit
2. Simulation running
3. Serial Monitor
4. Bright room/no motion
5. Dark room/motion
6. High temperature
7. Normal temperature
8. Security armed
9. Intruder alert
10. Manual override
11. OLED dashboard
12. Final integrated system

## Pass Criteria

A test is PASS when the observed output matches the expected behavior without firmware errors or unexpected actuator transitions.
