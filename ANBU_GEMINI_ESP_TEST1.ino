/*
 * ESP32_AI_Connect - Gemini Chatbot with Web + OLED + LED
 * Author: ANBU_SELVAN+GEMINI
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ESP32_AI_Connect.h>
#include <U8g2lib.h>

#define LED_PIN 2   // LED indicator pin

const char* ssid = "ssid";
const char* password = "wifi_pass;
const char* apiKey   = "your key";
const char* model    = "gemini-2.0-flash";
const char* platform = "gemini";

ESP32_AI_Connect aiClient(platform, apiKey, model);
WebServer server(80);

// OLED Display (NFP1315 / SSD1315 Compatible)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// ===== FILTER RESPONSE =====
String filterResponse(const String &rawResponse) {
  if (rawResponse.length() == 0) return "No valid response received.";
  String r = rawResponse;
  r.replace("As an AI language model,", "");
  r.replace("As an AI model,", "");
  r.replace("I am an AI model,", "");
  r.trim();
  return (r.length() > 0) ? r : "No valid response received.";
}

// ===== CONNECT WIFI =====
void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected ✅");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi failed! Retrying...");
    delay(2000);
    connectWiFi();
  }
}

// ===== LED + CIRCULAR ANIMATION =====
void showThinkingAnimation() {
  digitalWrite(LED_PIN, HIGH);
  for (int frame = 0; frame < 40; frame++) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    int cx = 64, cy = 32, r = 20;
    for (int i = 0; i < 8; i++) {
      float angle = (frame * 0.3) + (i * 0.78);
      int x = cx + cos(angle) * r;
      int y = cy + sin(angle) * r;
      u8g2.drawDisc(x, y, 3, U8G2_DRAW_ALL);
    }
    u8g2.sendBuffer();
    delay(50);
  }
  digitalWrite(LED_PIN, LOW);
}

// ===== SCROLLABLE OLED TEXT =====
void displayTextWithScroll(const String &text) {
  const int lineHeight = 10;
  const int maxLines = 5;
  int totalLines = (text.length() / 18) + 1;
  int scrollLimit = max(0, totalLines - maxLines);

  for (int offset = 0; offset <= scrollLimit * lineHeight; offset++) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    int y = 10 - offset;
    for (int i = 0, pos = 0; i < totalLines; i++, pos += 18) {
      String line = text.substring(pos, min((size_t)(pos + 18), text.length()));
      u8g2.drawStr(0, y + i * lineHeight, line.c_str());
    }
    u8g2.sendBuffer();
    delay(60);
  }
}

// ===== GET AI RESPONSE =====
String getAIResponse(const String &msg) {
  String res;
  for (int i = 0; i < 2; i++) {
    res = aiClient.chat(msg);
    if (res.length() > 0) break;
    delay(500);
  }
  return res;
}

// ===== WEB PAGE =====
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head>
<meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>ANBU-TEST-GPT-WEB-SERVER</title>
<style>
:root{--bg:#0b0f14;--accent:#58a6ff;--muted:#c9d1d9;}
body{margin:0;font-family:Arial,Roboto;background:var(--bg);color:var(--muted);display:flex;align-items:center;justify-content:center;height:100vh;}
.container{width:94%;max-width:700px;padding:20px;border-radius:12px;background:linear-gradient(180deg,rgba(255,255,255,0.02),rgba(255,255,255,0.01));box-shadow:0 6px 20px rgba(2,6,23,0.6);}
h1{color:var(--accent);margin-bottom:10px;}
form{display:flex;gap:8px;flex-wrap:wrap;}
input[type=text],input[type=number]{flex:1;padding:10px;border-radius:6px;border:1px solid rgba(255,255,255,0.06);background:#07101a;color:var(--muted);}
button{padding:10px 14px;border-radius:6px;border:none;background:var(--accent);color:#041028;cursor:pointer;}
.answer-box{margin-top:14px;padding:12px;border-radius:8px;background:#07121a;border:1px solid rgba(255,255,255,0.03);}
.qtext{background:#061018;padding:8px;border-radius:6px;white-space:pre-wrap;}
.astyle{margin-top:6px;font-size:14px;color:#dbe9ff;white-space:pre-wrap;}
.spinner{width:14px;height:14px;border:2px solid rgba(255,255,255,0.2);border-top-color:var(--accent);border-radius:50%;animation:spin 0.8s linear infinite;}
@keyframes spin{to{transform:rotate(360deg)}}
</style></head><body>
<div class="container"><h1>ANBU-TEST-GPT-WEB-SERVER</h1>
<form id="askForm" action="/ask" method="post" onsubmit="showLoading()">
<input type="text" name="question" placeholder="Type your question..." required>
<button type="submit">Ask Gemini</button></form>
<div id="loading" style="display:none;margin-top:10px;">
<div style="display:flex;align-items:center;gap:6px;"><div class="spinner"></div>
<span>Gemini is thinking...</span></div></div>
<div class="answer-box">
<div class="qtext">%QUESTION%</div>
<div class="astyle">%ANSWER%</div></div></div>
<script>function showLoading(){document.getElementById("loading").style.display="block";}</script>
</body></html>
)rawliteral";

// ===== HANDLERS =====
String lastQ = "", lastA = "";
void handleRoot() {
  String page = htmlPage;
  page.replace("%QUESTION%", lastQ);
  page.replace("%ANSWER%", lastA);
  server.send(200, "text/html", page);
}

void handleAsk() {
  if (!server.hasArg("question")) { 
    server.send(400, "text/plain", "No question!"); 
    return; 
  }

  lastQ = server.arg("question");
  Serial.println("📩 Web Query: " + lastQ);

  // --- Show question on OLED ---
  String queryText = "Query: " + lastQ;
  displayTextWithScroll(queryText);   // scroll question first

  // --- Show thinking animation ---
  showThinkingAnimation();

  // --- Get AI response ---
  String res = filterResponse(getAIResponse(lastQ));
  lastA = res;

  // --- Show AI response on OLED ---
  String aiText = "AI: " + res;
  displayTextWithScroll(aiText);      // scroll answer

  // --- Update web page ---
  handleRoot();
}
// ===== BOOT ANIMATION =====
void showBootAnimation() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);

  for (int i = 0; i < 3; i++) {
    u8g2.clearBuffer();
    u8g2.drawStr(15, 30, "GEMINI-GPT");
    u8g2.sendBuffer();
    delay(300);
    u8g2.clearBuffer();
    u8g2.drawStr(15, 30, "BY ANBU");
    u8g2.sendBuffer();
    delay(300);
  }

  // Final fade-in animation
  for (int y = 64; y >= 20; y -= 2) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_8x13B_tf);
    u8g2.drawStr(10, y, "GEMINI-GPT");
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(28, y + 16, "BY ANBU");
    u8g2.sendBuffer();
    delay(50);
  }

  delay(1000);
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  u8g2.begin();
  showBootAnimation(); 
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 10, "Connecting WiFi...");
  u8g2.sendBuffer();

  connectWiFi();

  u8g2.clearBuffer();
  u8g2.drawStr(0, 10, "IP:");
  u8g2.drawStr(0, 22, WiFi.localIP().toString().c_str());
  u8g2.sendBuffer();

  String params = R"({"topP":0.9,"temperature":0.6,"maxOutputTokens":100,"candidateCount":1})";
  aiClient.setChatParameters(params);

  server.on("/", handleRoot);
  server.on("/ask", HTTP_POST, handleAsk);
  server.begin();
  Serial.println("System Ready ✅");
}

// ===== LOOP =====
void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  server.handleClient();

  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg.length() > 0) {
      showThinkingAnimation();
      String res = filterResponse(getAIResponse(msg));
      displayTextWithScroll(res);
      lastQ = msg;
      lastA = res;
      Serial.println("AI: " + res);
    }
  }
}
