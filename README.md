# ESP32-BASED-GEMINI-AI-CHATBOT-WITH-WEBSERVER
GEMINI-GPT ESP32 Chatbot is an AI-powered embedded chatbot built with ESP32, featuring a web interface, OLED display, and LED animations. Users can ask questions via the web, and the ESP32 displays the query and AI response on the OLED with smooth scrolling and interactive animations. Developed by Anbu Selvan.

# GEMINI-GPT ESP32 Chatbot

**Author:** Anbu Selvan  
**Project:** GEMINI-GPT ESP32 AI Chatbot with Web, OLED, and LED Feedback  
**Date:** 2025  

---
# QUICK DEMO:


https://github.com/user-attachments/assets/ef5143b2-7efa-4f99-b709-1981e3db12a5


---

## 🔹 Project Overview

This project is an AI-powered chatbot built on the **ESP32** microcontroller using the **Gemini API**. It integrates:

- **OLED display** (SSD1315/compatible) for showing boot animation, queries, and AI responses.  
- **LED indicator** for visual feedback during AI processing.  
- **Web interface** for sending questions and receiving answers in real-time.  
- **Smooth scrolling and animations** for a modern, interactive experience.

The project demonstrates how embedded hardware can interact with cloud AI models, providing a compact and interactive AI assistant.

---

## 🔹 Features

- **Boot Animation:** Displays `GEMINI-GPT BY ANBU` with smooth fade-in animation on OLED.  
- **Wi-Fi Connectivity:** Connects to your network and displays IP address on OLED.  
- **Web Chat Interface:** User-friendly web page to ask questions to the Gemini AI model.  
- **LED Thinking Animation:** Blinking LED with circular pattern while AI is processing.  
- **OLED Question & Answer Display:**  
  - Displays `Query:` with your web question.  
  - Displays `AI:` with the AI-generated response.  
  - Scrolls long text smoothly.  
- **Fallback and Reliability:** Handles network reconnection automatically and filters invalid AI responses.

---

## 🔹 Hardware Required

- **ESP32 development board**  
- **OLED Display** (SSD1315 / NFP1315 compatible, 128×64)  
- **LED** (optional, built-in or external, connected to pin 2)  
- **USB cable** for programming and serial monitor  
![v-nodemcu-esp32-c](https://github.com/user-attachments/assets/2c5f5a03-9a33-4045-ad36-39f6957fb283) ![41C9LvJDlfL _AC_UF1000,1000_QL80_](https://github.com/user-attachments/assets/9ab59174-7555-4852-991a-156ffd3f3b1a)



---

## 🔹 Software Requirements

- **Arduino IDE** or compatible platform  
- **Libraries:**  
  - `WiFi.h`  
  - `WebServer.h`  
  - `ESP32_AI_Connect.h`  
  - `U8g2lib.h`  

- **Gemini API Key** (replace in code with your API credentials)

---

## 🔹 Installation and Setup

1. **Clone this repository** or download the ZIP file.  
2. **Open the project** in Arduino IDE.  
3. **Install required libraries** via Library Manager:  
   - `U8g2`  
   - `ESP32_AI_Connect`  
   - `WebServer`  
4. **Configure your Wi-Fi credentials** in the code:  
   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";

## 🔹 OUTPUT AND RESULT
<img width="1049" height="417" alt="Screenshot 2025-11-08 142020" src="https://github.com/user-attachments/assets/09c26c90-9824-4779-87f3-6a0b80a36499" />

![20251108_140510](https://github.com/user-attachments/assets/c3cb9094-a34a-4250-8fe2-f95f02393c77)
![20251108_140518](https://github.com/user-attachments/assets/51cdb987-6a90-4a4a-b908-5feb67ae678c)
![20251108_140606](https://github.com/user-attachments/assets/b1c90810-3891-480f-827e-0a10af9c5335)
<img width="1049" height="417" alt="Screenshot 2025-11-08 142020" src="https://github.com/user-attachments/assets/7edf8eda-765b-443d-bab0-72cf4ec06566" />
<img width="1182" height="657" alt="08 11 2025_12 24 07_REC" src="https://github.com/user-attachments/assets/71627e44-54fd-4af5-b0e7-0a9cb6ac4ccd" />

![20251108_141946](https://github.com/user-attachments/assets/08ea83ed-ac8b-4484-830e-1e08573c1451)
![20251108_140606](https://github.com/user-attachments/assets/099bd466-8ebf-4ade-acdc-bf5d67f77442)
![20251108_141946](https://github.com/user-attachments/assets/ab1fb402-526d-4b74-940f-f569dcf340e8)
