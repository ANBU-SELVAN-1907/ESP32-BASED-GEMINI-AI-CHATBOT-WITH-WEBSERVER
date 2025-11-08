# ESP32-BASED-GEMINI-AI-CHATBOT-WITH-WEBSERVER
GEMINI-GPT ESP32 Chatbot is an AI-powered embedded chatbot built with ESP32, featuring a web interface, OLED display, and LED animations. Users can ask questions via the web, and the ESP32 displays the query and AI response on the OLED with smooth scrolling and interactive animations. Developed by Anbu Selvan.

# GEMINI-GPT ESP32 Chatbot

**Author:** Anbu Selvan  
**Project:** GEMINI-GPT ESP32 AI Chatbot with Web, OLED, and LED Feedback  
**Date:** 2025  

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
