#ifndef WAJAH_H
#define WAJAH_H

// Definisikan tipe data Enum secara global
enum RobotMode { MODE_FACE };
enum Emotion { EMOT_BIASA, EMOT_SENANG, EMOT_MARAH, EMOT_SEDIH, EMOT_NGANTUK };

// Deklarasi variabel emosi global
extern Emotion currentEmotion;

// Deklarasi fungsi standar
void updateFacePhysics();
void updateLook();
void updateBlink();

#ifdef __cplusplus
// Kita gunakan forward declaration (void*) atau class pointer agar tidak perlu include SSD1306 di header
class Adafruit_SSD1306;
void drawFace(Adafruit_SSD1306 &display);
#endif

#endif // WAJAH_H
