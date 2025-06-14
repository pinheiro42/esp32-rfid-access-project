# esp32-rfid-access-project
ESP32-based RFID access control system with EEPROM state storage, relay control, LED and buzzer feedback.

# 🔐 ESP32 RFID Access Control System

This project is a simple RFID-based access control system using an ESP32. It reads RFID tags using the MFRC522 module and controls a relay based on authorized access. The system includes LED indicators, a buzzer for feedback, and persistent relay state storage using EEPROM.

## 📦 Features

- ✅ Grants or denies access based on RFID UID.
- 💾 Stores relay state in EEPROM (retained across resets).
- 🔄 Toggles relay state (e.g., to unlock/lock a door).
- 🔊 Buzzer + red LED for unauthorized access.
- 🟢 Green LED indicates relay is active (ON).
- 📟 Serial monitor for UID output and debugging.

## 🛠️ Hardware Used

- ESP32 (WROOM-32 or compatible)
- RC522 RFID reader module (MFRC522)
- Relay module (for door lock or device control)
- Red LED
- Green LED
- Buzzer
- RFID Tag/Card
- Breadboard & Jumper wires

## 📚 Libraries Required

Install the following libraries via Arduino Library Manager:

- `MFRC522` by Miguel Balboa
- `EEPROM` (built-in with ESP32 board support)
- `SPI` (built-in)

## 🔌 Pin Configuration

| Component      | ESP32 Pin |
|----------------|-----------|
| RFID SS (SDA)  | 5         |
| RFID RST       | 2         |
| LED RED        | 12        |
| LED GREEN      | 13        |
| BUZZER         | 27        |
| RELAY          | 26        |
| SPI (SCK/MOSI/MISO) | Default (18/23/19) |

## 🔄 System Behavior

- On startup:
  - Initializes hardware and reads the last saved relay state from EEPROM.
  - Restores relay and LED state accordingly.
- On RFID tag scan:
  - If the UID matches the authorized UID, toggles the relay state.
  - Saves new state to EEPROM.
  - If not authorized, activates buzzer and red LED for a short alert.

## 🔐 Change Authorized UID

Replace the UID in the code:
```cpp
byte authorizedUID[] = { 0xD3, 0x57, 0xB1, 0x0D }; // Change to your tag's UID
