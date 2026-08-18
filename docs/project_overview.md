# Project Overview

## Title

Smart Parking System using Ultrasonic Sensors

## Objective

Build a working smart parking prototype that detects free and occupied slots in real time, guides vehicles at an entry barrier, and shows live parking status locally and through a simple web page.

## Problem

Traditional parking management can require manual monitoring and gives drivers limited visibility into available spaces. The prototype automates slot detection and presents the current state immediately.

## Solution

Four HC-SR04 sensors monitor four parking slots. The ESP32 reads distance, filters the readings, applies a threshold, debounces state changes, counts free slots, and updates the OLED, LEDs, buzzer, servo, serial output, and web page.

## Industry relevance

The source project frames smart parking as useful in shopping malls, airports, hospitals, office buildings, smart cities, residential societies, railway stations, universities, and commercial parking facilities.

## Embedded concepts

- Microcontroller and GPIO
- Trigger/echo ultrasonic measurement
- Timers and pulse measurement
- Distance calculation
- Threshold-based state classification
- Digital output control
- I2C OLED communication
- Serial communication
- State tracking and debounce
- Servo control
- Wi-Fi/web status
