#ifndef WAJAH_H
#define WAJAH_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definisikan tipe data Enum secara global
enum RobotMode { MODE_FACE };
enum Emotion { EMOT_BIASA, EMOT_SENANG, EMOT_MARAH, EMOT_SEDIH, EMOT_NGANTUK };

// Deklarasi variabel emosi global agar bisa diubah dari application.cc
extern Emotion currentEmotion;

// Deklarasi fungsi standar
void updateFacePhysics();
void updateLook();
void updateBlink();

#ifdef __cplusplus
void drawFace(Adafruit_SSD1306 &display);
#endif

#endif // WAJAH_H
