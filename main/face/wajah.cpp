#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "wajah.h"

// Inisialisasi variabel emosi global
Emotion currentEmotion = EMOT_BIASA;

// Definisikan objek layar secara internal di sini (SDA=41, SCL=42)
static Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Variabel fisik wajah
static float faceX = 0, faceY = 0;
static float targetFaceX = 0, targetFaceY = 0;
static float velX = 0, velY = 0;
static float spring = 0.08, damping = 0.75;
static bool blinking = false;
static unsigned long lastBlink = 0, nextBlink = 0, lastLook = 0;

void initFaceDisplay() {
  Wire.begin(41, 42); // Menggunakan GPIO 41 dan 42 sesuai board_config.h
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Xiaozhi Booting...");
    display.display();
  }
}

void updateFacePhysics() {
  float ax = (targetFaceX - faceX) * spring;
  float ay = (targetFaceY - faceY) * spring;
  velX = (velX + ax) * damping; velY = (velY + ay) * damping;
  faceX += velX; faceY += velY;
}

void updateLook() {
  if (millis() - lastLook > 2000) {
    lastLook = millis();
    targetFaceX = random(-6, 7); targetFaceY = random(-4, 5);
  }
}

void updateBlink() {
  unsigned long now = millis();
  if (now > nextBlink) { blinking = true; lastBlink = now; nextBlink = now + random(3000, 7000); }
  if (blinking && (now - lastBlink > 120)) { blinking = false; }
}

void renderFaceLoop() {
  display.clearDisplay();
  
  int cx = 64 + faceX; int cy = 32 + faceY;
  int leftEyeX = cx - 26; int rightEyeX = cx + 26; int eyePosY = cy - 2;
  int pupilOffsetX = faceX * 0.4; int pupilOffsetY = faceY * 0.2;
  
  if (blinking) {
    display.drawFastHLine(leftEyeX - 16, eyePosY, 32, SSD1306_WHITE);
    display.drawFastHLine(rightEyeX - 16, eyePosY, 32, SSD1306_WHITE);
  } else {
    display.fillCircle(leftEyeX, eyePosY, 16, SSD1306_WHITE);
    display.fillCircle(rightEyeX, eyePosY, 16, SSD1306_WHITE);
    if (currentEmotion == EMOT_NGANTUK) {
      display.fillCircle(leftEyeX + pupilOffsetX, eyePosY + 4, 6, SSD1306_BLACK);
      display.fillCircle(rightEyeX + pupilOffsetX, eyePosY + 4, 6, SSD1306_BLACK);
      display.fillRect(leftEyeX - 16, eyePosY - 16, 32, 16, SSD1306_BLACK);
      display.fillRect(rightEyeX - 16, eyePosY - 16, 32, 16, SSD1306_BLACK);
    } else {
      display.fillCircle(leftEyeX + pupilOffsetX, eyePosY + pupilOffsetY, 7, SSD1306_BLACK);
      display.fillCircle(rightEyeX + pupilOffsetX, eyePosY + pupilOffsetY, 7, SSD1306_BLACK);
      display.fillCircle(leftEyeX + pupilOffsetX - 2, eyePosY + pupilOffsetY - 2, 2, SSD1306_WHITE);
      display.fillCircle(rightEyeX + pupilOffsetX - 2, eyePosY + pupilOffsetY - 2, 2, SSD1306_WHITE);
      if (currentEmotion == EMOT_MARAH) {
        display.fillTriangle(leftEyeX - 16, eyePosY - 16, leftEyeX + 16, eyePosY - 16, leftEyeX + 16, eyePosY - 4, SSD1306_BLACK);
        display.fillTriangle(rightEyeX - 16, eyePosY - 16, rightEyeX + 16, eyePosY - 16, rightEyeX - 16, eyePosY - 4, SSD1306_BLACK);
      } else if (currentEmotion == EMOT_SEDIH) {
        display.fillTriangle(leftEyeX - 16, eyePosY - 16, leftEyeX + 16, eyePosY - 16, leftEyeX - 16, eyePosY - 4, SSD1306_BLACK);
        display.fillTriangle(rightEyeX - 16, eyePosY - 16, rightEyeX + 16, eyePosY - 16, rightEyeX + 16, eyePosY - 4, SSD1306_BLACK);
      }
    }
  }
  if (currentEmotion == EMOT_SENANG) display.fillTriangle(cx - 10, cy + 18, cx + 10, cy + 18, cx, cy + 28, SSD1306_WHITE);
  else if (currentEmotion == EMOT_SEDIH || currentEmotion == EMOT_MARAH) { display.fillRoundRect(cx - 9, cy + 25, 20, 4, 2, SSD1306_WHITE); display.fillRect(cx - 9, cy + 27, 20, 3, SSD1306_BLACK); }
  else if (currentEmotion == EMOT_NGANTUK) { display.fillRoundRect(cx - 6, cy + 22, 12, 3, 1, SSD1306_WHITE); display.fillRect(cx - 6, cy + 24, 12, 2, SSD1306_BLACK); }
  else display.fillRoundRect(cx - 9, cy + 23, 20, 4, 2, SSD1306_WHITE);

  display.display();
}
