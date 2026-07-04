#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "system_reset.h"
#include "application.h"
#include "button.h"
#include "assets/lang_config.h"
#include "led/single_led.h"

#include "board_config.h"  // <- Sangat penting, mengambil konfigurasi dari direktori saat ini
#include <wifi_station.h>

#include <esp_log.h>

#define TAG "SeeedStudioS3WifiBoard"

// Kelas ini merepresentasikan motherboard XIAO ESP32-S3.
class SeeedStudioS3WifiBoard : public WifiBoard {
private:
    Button boot_button_;
    Button touch_button_;
    Button volume_up_button_;
    Button volume_down_button_;

    void InitButtons() {
        // Tombol Touch: Mengatur logika tekan-untuk-bicara (Press-to-talk)
        touch_button_.OnPressDown([this]() {
            Application::GetInstance().StartListening();
        });
        touch_button_.OnPressUp([this]() {
            Application::GetInstance().StopListening();
        });
    }

public:
    SeeedStudioS3WifiBoard() :
        boot_button_(BOOT_BUTTON_GPIO),
        touch_button_(TOUCH_BUTTON_GPIO),
        volume_up_button_(VOLUME_UP_BUTTON_GPIO),
        volume_down_button_(VOLUME_DOWN_BUTTON_GPIO) {

        ESP_LOGI(TAG, "Init SeeedStudioS3WifiBoard");
        InitButtons();
    }

    virtual Led* GetLed() override {
        static SingleLed led(BUILTIN_LED_GPIO);
        return &led;
    }

    virtual AudioCodec* GetAudioCodec() override {
#ifndef AUDIO_I2S_METHOD_SIMPLEX
        static NoAudioCodecDuplex audio_codec(
            AUDIO_INPUT_SAMPLE_RATE,
            AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_BCLK,
            AUDIO_I2S_GPIO_WS,
            AUDIO_I2S_GPIO_DOUT,
            AUDIO_I2S_GPIO_DIN
        );
#else
        static NoAudioCodecSimplex audio_codec(
            AUDIO_INPUT_SAMPLE_RATE,
            AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_SPK_GPIO_BCLK,
            AUDIO_I2S_SPK_GPIO_LRCK,
            AUDIO_I2S_SPK_GPIO_DOUT,
            AUDIO_I2S_MIC_GPIO_SCK,
            AUDIO_I2S_MIC_GPIO_WS,
            AUDIO_I2S_MIC_GPIO_DIN
        );
#endif
        return &audio_codec;
    }

    // WAJIB ADA: Mengembalikan nullptr karena display di-handle oleh Adafruit di application.cc
    virtual Display* GetDisplay() override {
        return nullptr;
    }
};

// Daftarkan board ini agar bisa digunakan oleh sistem Xiaozhi
DECLARE_BOARD(SeeedStudioS3WifiBoard);
