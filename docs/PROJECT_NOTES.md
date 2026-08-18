# Project Notes

## Design Decisions

### Why no breadboard in Wokwi?
A breadboard does not execute control logic. It provides physical connection points in a real prototype. In a virtual simulation, direct component-to-component wiring is sufficient and produces a cleaner diagram.

### Why GPIO34 for the LDR?
GPIO34 is an ESP32 input-only ADC-capable pin, making it suitable for reading the photoresistor's analog output.

### Why use hysteresis for the fan?
The fan uses:
- ON at 30 °C
- OFF at 28 °C

This prevents rapid toggling if temperature fluctuates around the threshold.

### Why use `INPUT_PULLUP` for buttons?
It eliminates the need for external pull-up resistors in the virtual prototype. The button is active LOW.

### Why represent appliances with LEDs?
The Wokwi version is a safe logic-level demonstration. A real build would use properly rated transistor/MOSFET or relay driver stages for physical loads.

## Report Alignment

The implementation demonstrates:
- sensor integration
- automatic lighting
- temperature-based fan control
- security monitoring
- manual override
- OLED status display
- serial diagnostics
- integrated virtual testing
