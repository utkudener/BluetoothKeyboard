#include <BleKeyboard.h>
#include <BLEDevice.h>
#include <PS2Keyboard.h>

#define DATA_PIN 13  // PS/2 klavye veri pini
#define CLOCK_PIN 14 // PS/2 klavye saat pini

// PS2 özel tuş kodlarını tanımla
#define PS2_BACKSPACE 0x7F
#define PS2_TAB       0x09
#define PS2_ENTER     0x0D
#define PS2_SPACE     ' '    // Space boşluk karakteri olarak gelir
#define PS2_ESC       0x1B

#define PS2_UPARROW   0xB
#define PS2_DOWNARROW 0xA
#define PS2_LEFTARROW 0x8
#define PS2_RIGHTARROW 0x15
#define PS2_CTRL      0x14  // Ctrl
#define PS2_ALT       0x11  // Alt
#define PS2_SHIFT     0x12  // Shift

PS2Keyboard keyboard;
BleKeyboard bleKeyboard("ESP32_Keyboard", "DIY", 100);
BLEAdvertising* pAdvertising; 
bool wasConnected = false; 

// Bluetooth reklamlarını başlatan fonksiyon
void startAdvertising() {
    Serial.println("Bluetooth reklamları başlatılıyor...");
    pAdvertising->stop();
    delay(100);
    pAdvertising->start();
    Serial.println("Bluetooth reklamları aktif.");
}

void setup() {
    Serial.begin(115200);
    Serial.println("PS/2 Klavye ve BLE Klavye başlatılıyor...");

    // PS/2 Klavyeyi başlat
    keyboard.begin(DATA_PIN, CLOCK_PIN);  
    Serial.println("PS/2 Klavye Testi - Bir tuşa basın.");
    
    // Bluetooth Güç Seviyesi
    BLEDevice::setPower(ESP_PWR_LVL_P9);  
    BLEDevice::setMTU(517);  

    // BLE Klavyeyi Başlat
    bleKeyboard.begin();

    // BLE Reklam (Advertising) Ayarları
    pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->setMinInterval(0x20);
    pAdvertising->setMaxInterval(0x40);
    startAdvertising();
}

void loop() {
    if (keyboard.available()) {
        char c = keyboard.read();
        Serial.print("Tuş Basıldı: ");
        Serial.print(c);          // ASCII olarak yazdır
        Serial.print(" | HEX: 0x");
        Serial.println(c, HEX);   // HEX kodunu yazdır
        
        if (bleKeyboard.isConnected()) {
            // Özel tuşları kontrol et
            switch (c) {
                case PS2_ENTER:
                    Serial.println("Enter Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_RETURN);
                    break;
                case PS2_BACKSPACE:
                    Serial.println("Backspace Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_BACKSPACE);
                    break;
                case PS2_SPACE:
                    Serial.println("Space Tuşu Gönderildi.");
                    bleKeyboard.write(' ');
                    break;
                case PS2_TAB:
                    Serial.println("Tab Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_TAB);
                    break;
                case PS2_ESC:
                    Serial.println("ESC Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_ESC);
                    break;
                //case PS2_DELETE:
                   // Serial.println("Delete Tuşu Gönderildi.");
                   // bleKeyboard.write(KEY_DELETE);
                   // break;  
                case PS2_UPARROW:
                    Serial.println("Yukarı Ok Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_UP_ARROW);
                    break;
                case PS2_DOWNARROW:
                    Serial.println("Aşağı Ok Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_DOWN_ARROW);
                    break;
                case PS2_LEFTARROW:
                    Serial.println("Sol Ok Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_LEFT_ARROW);
                    break;
                case PS2_RIGHTARROW:
                    Serial.println("Sağ Ok Tuşu Gönderildi.");
                    bleKeyboard.write(KEY_RIGHT_ARROW);
                    break;
                case PS2_CTRL:
                    Serial.println("Ctrl Tuşu Gönderildi.");
                    bleKeyboard.press(KEY_LEFT_CTRL);
                    delay(10);
                    bleKeyboard.release(KEY_LEFT_CTRL);
                    break;
                case PS2_ALT:
                    Serial.println("Alt Tuşu Gönderildi.");
                    bleKeyboard.press(KEY_LEFT_ALT);
                    delay(10);
                    bleKeyboard.release(KEY_LEFT_ALT);
                    break;
                case PS2_SHIFT:
                    Serial.println("Shift Tuşu Gönderildi.");
                    bleKeyboard.press(KEY_LEFT_SHIFT);
                    delay(10);
                    bleKeyboard.release(KEY_LEFT_SHIFT);
                    break;
                default:
                    Serial.print("Normal Tuş Gönderildi: ");
                    Serial.println(c);
                    bleKeyboard.print(c);
                    break;
            }
        }
    }

    // Bağlantı Kontrolü ve Kopunca Yeniden Bağlanma
    if (bleKeyboard.isConnected()) {
        if (!wasConnected) {
            Serial.println("Bluetooth bağlantısı sağlandı!");
            wasConnected = true;
        }
    } else {
        if (wasConnected) {
            Serial.println("Bluetooth bağlantısı kesildi, yeniden bağlanılıyor...");
            wasConnected = false;
            startAdvertising();
        }
    }

    delay(20);
}
