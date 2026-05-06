🛡️ ElderGuard – Smart Sanitation Alert System for Elderly Safety

An IoT-based embedded system designed to monitor elderly individuals and automatically detect possible emergency situations such as immobility or falls, ensuring timely assistance through alerts.

📌 Overview

ElderGuard is a smart safety solution that continuously monitors movement using sensors. If no motion is detected for a predefined time, the system assumes a potential emergency and triggers alerts both locally and remotely.

This project aims to improve elderly care by providing a low-cost, real-time monitoring system.

🚀 Features
🔍 Real-time motion monitoring using PIR sensor
🚨 Automatic emergency detection (no movement condition)
🔊 Buzzer alert for nearby people
📲 Instant notification via Telegram bot
⚡ Low-cost and energy-efficient system
🔧 Easy to install and use
🛠️ Hardware Components
Microcontroller (Arduino / ESP8266 / ESP32)
PIR Motion Sensor
Buzzer
Wi-Fi Module (if using Arduino)
Power Supply
💻 Software & Technologies
Embedded C / Arduino IDE
IoT Communication (Wi-Fi)
Telegram Bot API
Serial Monitoring for debugging
⚙️ Working Principle
The PIR sensor continuously detects motion.
If movement is detected → system stays idle.
If no movement is detected for a specific time:
Buzzer is activated
Telegram alert is sent to caregiver
Caregiver can take immediate action.
📊 System Architecture
[PIR Sensor] → [Microcontroller] → [Decision Logic]
                                     ↓
                     ┌───────────────┴───────────────┐
                     ↓                               ↓
                [Buzzer Alert]           [Telegram Notification]
📸 Demo / Output

(Add images or screenshots here)

🔧 Installation & Setup

Clone the repository:

git clone https://github.com/your-username/elderguard.git
Open the code in Arduino IDE
Install required libraries:
WiFi library
Telegram Bot library
Configure:
WiFi credentials
Telegram Bot Token
Chat ID
Upload the code to the microcontroller
📈 Future Enhancements
Fall detection using accelerometer
Mobile app integration
GPS tracking for outdoor monitoring
AI-based behavior analysis
Battery backup system
