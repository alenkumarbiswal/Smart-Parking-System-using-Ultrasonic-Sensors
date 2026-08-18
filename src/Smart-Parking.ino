#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============================================================
// SMART PARKING SYSTEM USING ULTRASONIC SENSORS
// Target Board: ESP32 DevKit V4
// Author: Alen Kumar Biswal
// ============================================================

#define TOTAL_SLOTS 4
const float OCCUPIED_THRESHOLD_CM = 35.0; // Distance threshold for vehicle detection

// OLED Configuration (128x64 I2C)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Hardware Actuator Pins
#define SERVO_PIN 18
#define BUZZER_PIN 19
#define SERVO_PWM_CH 4

const int GATE_CLOSED_ANGLE = 0;
const int GATE_OPEN_ANGLE = 90;

// Sensor Pin Mapping: Slot 1 (left) to Slot 4 (right)
const uint8_t TRIG_PINS[TOTAL_SLOTS] = {5, 16, 27, 25};
const uint8_t ECHO_PINS[TOTAL_SLOTS] = {17, 4, 26, 33};

// LED Pin Mapping:
// Red LEDs (led1 - led4) -> Occupied
const uint8_t RED_LEDS[TOTAL_SLOTS]   = {13, 12, 14, 23};
// Green LEDs (led5 - led8) -> Free
const uint8_t GREEN_LEDS[TOTAL_SLOTS] = {32, 15, 2, 0};

// State Variables
bool slotOccupied[TOTAL_SLOTS] = {false, false, false, false};
float slotDistances[TOTAL_SLOTS] = {100.0, 100.0, 100.0, 100.0};
bool parkingFull = false;

unsigned long lastScanTime = 0;
unsigned long lastDisplayTime = 0;
unsigned long lastSerialLog = 0;

// ------------------------------------------------------------
// SERVO HARDWARE PWM CONTROL
// ------------------------------------------------------------
void setServoAngle(int angle) {
  // Map 0-180 deg to duty cycle on 14-bit resolution at 50Hz (ESP32 LEDC)
  int duty = 410 + ((float)angle / 180.0) * (2048 - 410);
  ledcWrite(SERVO_PWM_CH, duty);
}

// ------------------------------------------------------------
// SENSOR DISTANCE MEASUREMENT
// ------------------------------------------------------------
float measureDistance(uint8_t trigPin, uint8_t echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 18ms timeout prevents freezing/delays if sensor doesn't reflect
  unsigned long duration = pulseIn(echoPin, HIGH, 18000);
  if (duration == 0) return 100.0; // Default to free if out of range
  return (float)(duration / 58.0);
}

// ------------------------------------------------------------
// AVAILABILITY CALCULATION
// ------------------------------------------------------------
int countAvailableSlots() {
  int freeCount = 0;
  for (int i = 0; i < TOTAL_SLOTS; i++) {
    if (!slotOccupied[i]) freeCount++;
  }
  return freeCount;
}

// ------------------------------------------------------------
// OLED DISPLAY INTERFACE
// ------------------------------------------------------------
void renderDisplay(int freeCount) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("SMART PARKING SYSTEM");

  display.setCursor(0, 16);
  display.print("Available: ");
  display.print(freeCount);
  display.print(" / 4");

  display.setCursor(0, 32);
  display.print("S1:"); display.print(slotOccupied[0] ? "OCC" : "FREE");
  display.print(" S2:"); display.print(slotOccupied[1] ? "OCC" : "FREE");

  display.setCursor(0, 46);
  display.print("S3:"); display.print(slotOccupied[2] ? "OCC" : "FREE");
  display.print(" S4:"); display.print(slotOccupied[3] ? "OCC" : "FREE");

  display.setCursor(0, 56);
  if (freeCount == 0) {
    display.println("** PARKING FULL **");
  } else {
    display.print("Gate Status: OPEN");
  }
  display.display();
}

// ------------------------------------------------------------
// INITIALIZATION
// ------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("\n==========================================");
  Serial.println(" SMART PARKING SYSTEM INITIALIZATION");
  Serial.println("==========================================");

  // Initialize Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize Ultrasonic Sensors & Slot Status LEDs
  for (int i = 0; i < TOTAL_SLOTS; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
    pinMode(RED_LEDS[i], OUTPUT);
    pinMode(GREEN_LEDS[i], OUTPUT);

    // Initial State: All Free (Green ON, Red OFF)
    digitalWrite(GREEN_LEDS[i], HIGH);
    digitalWrite(RED_LEDS[i], LOW);
  }

  // Initialize Hardware PWM for Barrier Gate Servo
  ledcSetup(SERVO_PWM_CH, 50, 14);
  ledcAttachPin(SERVO_PIN, SERVO_PWM_CH);
  setServoAngle(GATE_OPEN_ANGLE); // Start with barrier gate open

  // Initialize I2C OLED (SDA: GPIO 21, SCL: GPIO 22)
  Wire.begin(21, 22);
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.display();
    Serial.println("OLED Display initialized successfully.");
  } else {
    Serial.println("ERROR: OLED Display initialization failed!");
  }

  renderDisplay(4);
  Serial.println("System Ready. All 4 slots available.");
}

// ------------------------------------------------------------
// MAIN LOOP
// ------------------------------------------------------------
void loop() {
  unsigned long currentMillis = millis();

  // 1. Scan Ultrasonic Sensors (Every 150 ms)
  if (currentMillis - lastScanTime >= 150) {
    lastScanTime = currentMillis;

    for (int i = 0; i < TOTAL_SLOTS; i++) {
      float distance = measureDistance(TRIG_PINS[i], ECHO_PINS[i]);
      slotDistances[i] = distance;
      slotOccupied[i] = (distance < OCCUPIED_THRESHOLD_CM);

      // Update Physical LEDs
      digitalWrite(GREEN_LEDS[i], slotOccupied[i] ? LOW : HIGH);
      digitalWrite(RED_LEDS[i],   slotOccupied[i] ? HIGH : LOW);
    }

    int freeCount = countAvailableSlots();
    parkingFull = (freeCount == 0);

    // Actuator Gate and Alarm Logic
    if (parkingFull) {
      setServoAngle(GATE_CLOSED_ANGLE); // Close Barrier Gate
      digitalWrite(BUZZER_PIN, HIGH);     // Sound Alert
    } else {
      setServoAngle(GATE_OPEN_ANGLE);   // Keep Barrier Open
      digitalWrite(BUZZER_PIN, LOW);      // Silence Buzzer
    }
  }

  // 2. Refresh OLED UI (Every 300 ms)
  if (currentMillis - lastDisplayTime >= 300) {
    lastDisplayTime = currentMillis;
    renderDisplay(countAvailableSlots());
  }

  // 3. Serial Monitor Telemetry (Every 1000 ms)
  if (currentMillis - lastSerialLog >= 1000) {
    lastSerialLog = currentMillis;
    Serial.printf("S1: %3.0fcm | S2: %3.0fcm | S3: %3.0fcm | S4: %3.0fcm | Free: %d/4 | Gate: %s\n",
                  slotDistances[0], slotDistances[1], slotDistances[2], slotDistances[3],
                  countAvailableSlots(), parkingFull ? "CLOSED (FULL)" : "OPEN");
  }
}