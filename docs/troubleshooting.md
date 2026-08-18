# Troubleshooting

## Wires do not appear

1. Replace the entire `diagram.json`, not only the parts section.
2. Ensure every connection is an array:
   `["esp:5", "ultrasonic1:TRIG", "green", []]`
3. Save and reload the Wokwi project.

## OLED stays blank

- Check I2C address `0x3C`.
- Check SDA GPIO21 and SCL GPIO22.
- Confirm Adafruit GFX and SSD1306 libraries.

## Sensor always reads invalid/high distance

- Confirm TRIG/ECHO pins match `diagram.json`.
- Ensure the sensor is selected and a valid distance is entered in Wokwi.
- Check Serial Monitor.

## Servo does not move

- Confirm GPIO18.
- Confirm the simulation uses the current ESP32 LEDC API.
- The servo is a demonstration actuator and moves on the gate cycle.

## GPIO0 warning

GPIO0 is used only for the Slot 4 red LED in the supplied virtual diagram. It is not recommended as the final physical-hardware choice.

## Wokwi firmware path error

If using Wokwi CLI, build the sketch first so the binary referenced by `simulation/wokwi.toml` exists. For the browser-based Wokwi editor, the TOML file is not required for normal simulation.

## Wi-Fi does not connect

The simulation uses `Wokwi-GUEST` with an empty password. The parking logic, OLED, LEDs, buzzer, and servo do not depend on Wi-Fi connectivity.
