# IoT Smart Gas Leakage Detector 🛡️

## 🚀 Project Overview
An automated safety system built on the **ESP32** microcontroller using **C++**. This project detects hazardous gas concentrations (LPG/Smoke) in real-time and provides both local (Buzzer) and remote (Telegram) notifications to ensure user safety.

## 🛠️ Tech Stack & Components
- **Microcontroller:** ESP32 (WROOM-32)
- **Programming Language:** C++ (Arduino Framework)
- **Sensor:** MQ-2 / MQ-5 Gas Sensor
- **Protocol:** HTTP (REST API) / WiFi
- **Alert System:** Telegram Bot API & Piezo Buzzer

## ✨ Key Features
- **Real-time Monitoring:** Continuous polling of analog gas levels.
- **Intelligent Alerting:** Integrated with a Telegram Bot to send instant push notifications to the user's smartphone.
- **Fail-safe Mechanism:** Local audible alarm (Buzzer) triggers even if WiFi connectivity is lost.
- **Threshold Calibration:** Software-defined sensitivity to prevent false triggers in kitchen environments.



## 📋 System Architecture
1. **Data Acquisition:** The ESP32 reads analog values from the MQ sensor.
2. **Logic Processing:** If the concentration exceeds the defined `THRESHOLD`, the system enters "Alert Mode."
3. **Communication:** - Triggers a Digital High to the Buzzer.
    - Establishes a Secure WiFi connection.
    - Sends a JSON-formatted POST request to the Telegram Bot API.

## 📂 Repository Structure
- `gas_detector_main.cpp`: Main firmware logic.
- `secrets.h`: (Template) Configuration for WiFi SSID and Bot Token.
- `Circuit_Diagram.png`: Hardware wiring schematic.

## 🚀 How to Use
1. Clone the repository.
2. Update the `secrets.h` file with your WiFi credentials and Telegram Bot Token.
3. Flash the code to your ESP32 using VS Code (PlatformIO) or Arduino IDE.
4. Monitor gas levels via the Serial Monitor or the Telegram App.
