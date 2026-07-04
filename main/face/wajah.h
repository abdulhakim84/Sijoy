#ifndef WAJAH_H
#define WAJAH_H

// Definisikan tipe data Enum secara global
enum RobotMode { MODE_FACE };
enum Emotion { EMOT_BIASA, EMOT_SENANG, EMOT_MARAH, EMOT_SEDIH, EMOT_NGANTUK };

// Deklarasi variabel emosi global agar bisa diubah dari application.cc
extern Emotion currentEmotion;

// Deklarasi fungsi standar wajah
void initFaceDisplay();
void updateFacePhysics();
void updateLook();
void updateBlink();
void renderFaceLoop();

#endif // WAJAH_H
