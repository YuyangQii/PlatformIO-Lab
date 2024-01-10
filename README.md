# PlatformIO-Lab

# #Wearable Device Project

## Introduction
This repository contains the source code for a wearable device project developed using PlatformIO. Utilizing the MPU6050 sensor, the device detects wrist movements to generate random dice rolls. This project is built using Adafruit QT Py SAMD21, MPU6050, BME280, SSD1306 OLED, a linear vibration actuator, and a blue LED.

## Features
- Dice Roll Simulation: Detects wrist movements to generate a random number (1-6), using MPU6050.
- Feedback Mechanisms: 
  - Visual: Blue LED blinks according to the dice number.
  - Tactile: Linear vibration actuator vibrates corresponding to the dice number.
- Environmental Data Display: When the wrist is stationary, the SSD1306 OLED displays environmental data (temperature, humidity, and pressure) from the BME280 sensor.
- Wearable Design: Configured as a wristband for easy and practical use.

## Hardware Requirements
- Adafruit QT Py SAMD21
- MPU6050 sensor
- BME280 sensor
- SSD1306 OLED display
- Linear Vibration Actuator
- 1 Blue LED
- Appropriate resistors and wiring
- Wristband casing for wearable format

## Software Requirements
- PlatformIO IDE or Arduino IDE
- Necessary libraries for MPU6050, BME280, SSD1306, etc.
