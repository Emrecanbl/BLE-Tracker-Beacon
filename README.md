# BLE Tracker Beacon
BLE Keychain Project
Project Overview
This project demonstrates a Bluetooth Low Energy (BLE) keychain device based on the nRF52840 SoC, designed to control a buzzer and provide status feedback through two RGB LEDs. The device includes:

A BLE service to control a buzzer, enabling the Find My Item feature.
A button service that can be extended to implement a Find My Phone feature.
A notification system for battery level measurement using ADC.

This project showcases skills in:

Bluetooth Low Energy (BLE) communication.
Multithreading with Zephyr RTOS.
Power-saving techniques using real-time task management.
Embedded system design, including hardware-software integration.
Features
BLE Output Control Service:

Controls a buzzer, which can be triggered remotely via BLE to help locate lost items (e.g., keychain or other objects attached to the device).
Initially designed for LED control but refocused on buzzer functionality to provide a Find My Item feature.
Button Interaction:

The button can be used to trigger various actions.
A Find My Phone feature can be implemented in the mobile application, where pressing the button sends a notification to the connected phone.
Battery Level Monitoring:

The device uses ADC to monitor the battery level.
Battery status is sent to the connected BLE device via notifications.
LED Status Indicators (Not controlled by the user):

Red LED blinks when the device is powered on but not connected.
Green LED blinks when the device is connected via BLE.
Red LED stays on when the BLE connection is lost.
Both the buzzer and LEDs remain continuously active if Bluetooth initialization fails.
These LEDs are used solely for device status indication and are not available for user interaction or control.
Power-Saving Mode:

The system uses a Wait_thread that suspends other tasks when no Bluetooth connection is active to conserve power.

Multithreading:

The system is managed with three threads:
send_data_thread: Periodically sends battery data via BLE notifications.
Ring_thread: Manages the LED blinking patterns depending on the connection status.
Wait_thread: Handles idle waiting and power-saving when there is no active Bluetooth connection.
Hardware Setup
nRF52840 SoC
Buzzer connected for audible alerts and the Find My Item feature.
Two RGB LEDs for status feedback (not user-controlled).
Button for user interaction.
ADC for battery level monitoring.
Software Components
Nordic nRF SDK for BLE communication.
Zephyr RTOS for multithreading and task management.
GATT Services:
Custom UUIDs are used for buzzer control, button interaction, and battery level notifications.
BLE Services
Output Control Service
UUID: 0x1234
Characteristics:
Write: Controls the buzzer based on specific events or conditions, such as triggering the Find My Item feature when activated through the connected BLE device.
Notify: Sends notifications (e.g., battery level or other status).
Button Service
UUID: 0x5678
Characteristics:
Read: Reads the button state and can be used to trigger a Find My Phone feature in the mobile application.
Battery Level Notification
UUID: 0x9ABC
Notify: Sends battery level data based on ADC readings.
How It Works
Advertising: The device advertises itself with a custom BLE name and UUIDs for the services.
BLE Connection: When a device connects, it can control the buzzer through the output control characteristic, enabling the Find My Item feature.
Battery Monitoring: Battery levels are periodically sent via BLE notifications.
Find My Phone Feature: If implemented in the mobile app, pressing the button sends a signal to trigger a phone alarm.
Power-Saving Mode: The device enters a low-power state when not connected to a BLE device.
Getting Started
Clone the Repository:

bash
Kodu kopyala
git clone https://github.com/yourusername/ble-keychain.git
cd ble-keychain

Build and Flash the Code:

Use the nRF Connect SDK or Zephyr RTOS to build the project.
Flash the firmware to your nRF52840 development board.
Test with BLE Device:

Use a BLE scanner (e.g., nRF Connect app) to connect to the keychain device.
Control the buzzer via the app to trigger the Find My Item feature, and monitor battery levels.
Future Improvements
Implement the Find My Phone feature in the mobile application.
Enhance the battery level monitoring with more precise thresholds.
Add more sensor integrations, such as temperature or humidity, to extend the functionality.
Project Status
Software and hardware are fully functional. The enclosure design is currently in progress to complete the device assembly.

