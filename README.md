Thermal Comfort Monitoring System

Overview

An Arduino-based system using FreeRTOS to monitor and regulate temperature and pressure in buildings, featuring real-time LCD display and automated/manual control modes.

Features

Automatic & Manual Control: Toggle via push button.

Temperature & Pressure Monitoring: Simulated with potentiometers.

Heater & Pump Control: Activates based on thresholds.

LCD Display: Real-time data visualization.

FreeRTOS Multitasking: Efficient scheduling & synchronization.

Components

Hardware:

Arduino Uno, LCD (I2C), Potentiometers, Push Button, LED

Software:

Arduino IDE, Arduino_FreeRTOS.h, LiquidCrystal_I2C.h, Wire.h

Task Breakdown

Task_T: Reads & updates temperature.

Task_P: Monitors & regulates pressure.

Task_S: Updates LCD display.

Task_SW: Handles mode switching.

Setup & Usage

Connect components as per the circuit diagram.

Install Arduino IDE & required libraries.

Upload code to Arduino.

Use push button to toggle modes, adjust potentiometers to test.

Testing & Validation

Tested under various conditions for stability.

Automatic mode properly activates/deactivates devices.

Manual mode allows precise temperature setting.
