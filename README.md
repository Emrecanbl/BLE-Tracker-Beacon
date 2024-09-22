 BLE Tracker Beacon

## Project Overview
This project demonstrates a Bluetooth Low Energy (BLE) keychain device based on the nRF52840 SoC, designed to control a buzzer and provide status feedback through two RGB LEDs. The device includes:

- A BLE service to control a buzzer, enabling the Find My Item feature.
- A button service that can be extended to implement a Find My Phone feature.
- A notification system for battery level measurement using ADC.

### Skills Showcased
- Bluetooth Low Energy (BLE) communication
- Multithreading with Zephyr RTOS
- Power-saving techniques using real-time task management
- Embedded system design, including hardware-software integration
![Sample](https://github.com/Emrecanbl/BLE-Tracker-Beacon/blob/main/IMG_2.jpg?raw=true)
## Features

### BLE Output Control Service
- **Functionality:** Controls a buzzer remotely via BLE to help locate lost items (e.g., keychain or other objects).
- **Design Evolution:** Initially designed for LED control but refocused on buzzer functionality to enhance the Find My Item feature.

### Button Interaction
- **Usage:** The button can trigger various actions.
- **Find My Phone Feature:** Can be implemented in the mobile application, allowing users to send notifications to their connected phone.

### Battery Level Monitoring
- **Implementation:** Uses ADC to monitor the battery level.
- **Notifications:** Battery status is sent to the connected BLE device via notifications.

### LED Status Indicators (Not User-Controlled)
- **Red LED:** Blinks when the device is powered on but not connected; stays on when the BLE connection is lost.
- **Green LED:** Blinks when the device is connected via BLE.
- **Failure State:** Both the buzzer and LEDs remain active if Bluetooth initialization fails.

### Power-Saving Mode
- **Mechanism:** The system employs a Wait_thread that suspends other tasks when no Bluetooth connection is active to conserve power.

### Multithreading
The system is managed with three threads:
1. **send_data_thread:** Periodically sends battery data via BLE notifications.
2. **ring_thread:** Manages LED blinking patterns based on connection status.
3. **wait_thread:** Handles idle waiting and power-saving when there is no active Bluetooth connection.

## Hardware Setup
- **nRF52840 SoC**
- **Buzzer:** Connected for audible alerts and the Find My Item feature.
- **Two RGB LEDs:** For status feedback (not user-controlled).
- **Button:** For user interaction.
- **ADC:** For battery level monitoring.

## Software Components
- **Nordic nRF SDK:** For BLE communication.
- **Zephyr RTOS:** For multithreading and task management.

### GATT Services
Custom UUIDs are used for buzzer control, button interaction, and battery level notifications.

#### BLE Services
1. **Output Control Service**
   - **UUID:** 0x1234
   - **Characteristics:**
     - **Write:** Controls the buzzer based on specific events or conditions.
     - **Notify:** Sends notifications (e.g., battery level or other status).

2. **Button Service**
   - **UUID:** 0x5678
   - **Characteristics:**
     - **Read:** Reads the button state for potential Find My Phone feature activation.

3. **Battery Level Notification**
   - **UUID:** 0x9ABC
   - **Notify:** Sends battery level data based on ADC readings.

## How It Works
- **Advertising:** The device advertises itself with a custom BLE name and UUIDs for the services.
- **BLE Connection:** When a device connects, it can control the buzzer through the output control characteristic, enabling the Find My Item feature.
- **Battery Monitoring:** Battery levels are periodically sent via BLE notifications.
- **Find My Phone Feature:** If implemented in the mobile app, pressing the button sends a signal to trigger a phone alarm.
- **Power-Saving Mode:** The device enters a low-power state when not connected to a BLE device.
![Sample](https://github.com/Emrecanbl/BLE-Tracker-Beacon/blob/main/IMG_1.jpg?raw=true)
## Getting Started

### Clone the Repository
```bash
git clone https://github.com/yourusername/ble-keychain.git
cd ble-keychain
