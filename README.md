ENGLISH
Project Title: Converting PS/2 Keyboard to Bluetooth Wireless Keyboard (Using ESP32)

Prepared by: Utku Cavit DENER

1. Introduction

In this project, a system was developed that allows an old PS/2 interface keyboard to be used wirelessly with modern devices. Using the ESP32 microcontroller, data from the PS/2 keyboard is transmitted to computers, tablets, or mobile devices via the Bluetooth Low Energy (BLE) protocol. This allows obsolete or nostalgic PS/2 keyboards to integrate seamlessly with modern devices.

2. Components and Technologies Used

ESP32 Dev Kit: A microcontroller board with Bluetooth and Wi-Fi capabilities, offering low power consumption and high performance. With BLE HID support, it can be recognized as a keyboard input device.

PS/2 Keyboard: A keyboard that uses a 6-pin DIN connector and communicates via a synchronous clock (CLK) and data (DATA) lines.

Connections:

PS/2 DATA line: GPIO 13

PS/2 CLOCK line: GPIO 14

Software Libraries:

PS2Keyboard.h: A library that enables reading data from the PS/2 protocol.

BleKeyboard.h: A library that enables the ESP32 device to function as a BLE HID keyboard.

BLEDevice.h: A library used to configure the ESP32 BLE module and manage advertising broadcasts.

3. System Architecture and Operation Principles

The system operates in three main stages:

Reading from the PS/2 Keyboard:

The PS/2 keyboard is initialized using the keyboard.begin(DATA_PIN, CLOCK_PIN) function.

Data from the keyboard is received in synchronization with the clock signal.

ASCII or special key codes (ENTER, ESC, CTRL, etc.) are read using the keyboard.read() function.

Character Recognition and Conversion:

The incoming character data is matched with predefined special key codes.

If necessary, the data is converted into the appropriate key code for BLE HID protocol.

Depending on the character type, the data is sent using bleKeyboard.print() or bleKeyboard.write() functions.

BLE Connection and Status Monitoring:

The connection status is monitored using the bleKeyboard.isConnected() function.

If the connection is lost, the startAdvertising() function is used to restart advertising.

This ensures a stable and continuous connection experience.

4. Software Structure and Key Mapping

The code processes special characters separately. Here is an example of how this logic works:

cpp
Kopyala
Düzenle
if (keyboard.available()) {
    char c = keyboard.read();
    if (bleKeyboard.isConnected()) {
        switch (c) {
            case PS2_ENTER:
                bleKeyboard.write(KEY_RETURN);
                break;
            case PS2_BACKSPACE:
                bleKeyboard.write(KEY_BACKSPACE);
                break;
            // ... other special characters ...
            default:
                bleKeyboard.print(c);
                break;
        }
    }
}
This structure ensures that both basic characters (A, B, C, 1, 2...) and special function keys are accurately identified and transmitted.

Additionally, the press() and release() methods are used to handle keys that are held down, such as Shift and Ctrl.

5. Hardware and Development Environment Information

Hardware: ESP32 Devkit v1

Software Development Environment: Arduino IDE (with ESP32 support)

Board Settings:

Board: "ESP32 Dev Module"

Upload Speed: 921600

Flash Frequency: 80MHz

Partition Scheme: Default

Serial Communication Baud Rate: 115200

BLE Configurations:

BLE Transmission Power: Set to maximum using BLEDevice::setPower(ESP_PWR_LVL_P9)

MTU Value: 517 bytes (for higher data throughput)

Advertising Interval: Set to 0x20 (min) and 0x40 (max)

6. Testing Process and Challenges Encountered

Testing: The system was tested with different PS/2 keyboards and successfully connected to BLE-compatible devices (Android phones, Windows/Mac PCs).

Challenges Encountered:

Some older keyboards had different key codes than expected.

The BLE connection occasionally dropped (solution: automatic restart of advertising).

Some special characters (e.g., F1-F12) were not supported.

Improvements:

Support for key combinations (e.g., Ctrl+C)

Language selection and character mapping (e.g., Turkish Q/F keyboard)

Integration of battery and power-saving modes

7. Conclusion and Future Areas for Development

This project demonstrates how to repurpose old PS/2 keyboards for use with modern Bluetooth devices. It combines hardware knowledge, software development, and BLE protocol implementation, providing a comprehensive learning experience.

Future Recommendations:

BLE status feedback (e.g., LED to indicate connection status)

Portability with a built-in battery

Dual output (BLE and USB HID)

Physical button or serial command for keyboard layout selection

8. Appendix: Connection Diagram and Circuit Diagram (Optional)

Connections:

PS/2 DATA → GPIO13 (ESP32)

PS/2 CLOCK → GPIO14 (ESP32)

5V → ESP32 VIN

GND → GND

In case of debugging, serial port communication can be used.

References:
https://github.com/espressif/arduino-esp32

https://github.com/T-vK/ESP32-BLE-Keyboard

https://github.com/PaulStoffregen/PS2Keyboard

https://www.bluetooth.com/specifications/specs/human-interface-device-profile-1-1/


TÜRKÇE
Proje Adı: PS/2 Klavyeyi Bluetooth Kablosuz Klavyeye Dönüştürme (ESP32 ile)

Hazırlayan:Utku Cavit DENER 

1. Giriş

Bu projede, eski tip PS/2 arayüzüne sahip bir klavyenin, modern cihazlarla kablosuz olarak kullanılabilmesini sağlayan bir sistem geliştirilmiştir. Sistemde ESP32 mikrodenetleyicisi kullanılarak, PS/2 klavyeden gelen veri Bluetooth Low Energy (BLE) protokolü üzerinden bilgisayar, tablet veya mobil cihazlara aktarılmıştır. Bu sayede, artık üretimi yapılmayan veya nostaljik değeri olan PS/2 klavyeler, günümüz cihazlarıyla entegre çalışabilir hâle gelmiştir.

2. Kullanılan Bileşenler ve Teknolojiler

ESP32 Dev Kit: Bluetooth ve Wi-Fi özelliklerine sahip, düşük güç tüketimli ve yüksek performanslı bir mikrodenetleyici kartıdır. BLE HID desteği sayesinde, klavye gibi giriş cihazı olarak tanıtılabilir.

PS/2 Klavye: 6 pinli DIN konnektör kullanan, veri aktarımında senkron saat (CLK) ve veri (DATA) hatlarını kullanan bir klavye.

Bağlantılar:

PS/2 DATA hattı: GPIO 13

PS/2 CLOCK hattı: GPIO 14

Yazılım Kütüphaneleri:

PS2Keyboard.h: PS/2 protokolü üzerinden veri okuma işlemini gerçekleştiren kütüphane.

BleKeyboard.h: ESP32 cihazının BLE HID klavye olarak çalışmasını sağlayan kütüphane.

BLEDevice.h: ESP32 BLE modülünü yapılandırmak ve reklam yayınlarını yönetmek için kullanılır.

3. Sistem Mimarisi ve Çalışma Prensibi

Sistem 3 ana aşamada çalışır:

PS/2 Klavye Okuma:

keyboard.begin(DATA_PIN, CLOCK_PIN) fonksiyonu ile PS/2 klavye başlatılır.

Klavyeden gelen veri, saat sinyali ile eş zamanlı olarak alınır.

ASCII veya özel tuş kodları (ENTER, ESC, CTRL gibi) keyboard.read() ile okunur.

Karakter Tanıma ve Dönüştürme:

Gelen karakter verisi, tanımlı özel tuş kodları ile eşleştirilir.

Gerekirse BLE HID protokolü için uygun tuş koduna dönüştürülür.

Karakterin türüne göre bleKeyboard.print() ya da bleKeyboard.write() fonksiyonları ile gönderim sağlanır.

BLE Bağlantısı ve Durum Takibi:

bleKeyboard.isConnected() fonksiyonu ile bağlantı durumu izlenir.

Bağlantı kesilirse, startAdvertising() fonksiyonu ile yeniden reklam yayını başlatılır.

Bu sayede sistem, kesintisiz ve kararlı bir bağlantı deneyimi sunar.

4. Yazılımın Ana Yapısı ve Tuş Haritalama

Kodda özel karakterler ayrı ayrı işlenmiştir. Aşağıda bu mantığın örnek bir parçası gösterilmiştir:

if (keyboard.available()) {
    char c = keyboard.read();
    if (bleKeyboard.isConnected()) {
        switch (c) {
            case PS2_ENTER:
                bleKeyboard.write(KEY_RETURN);
                break;
            case PS2_BACKSPACE:
                bleKeyboard.write(KEY_BACKSPACE);
                break;
            // ... diğer özel karakterler ...
            default:
                bleKeyboard.print(c);
                break;
        }
    }
}

Bu yapı sayesinde, hem basit karakterler (A, B, C, 1, 2...) hem de özel işlev tuşları doğru şekilde tanımlanır ve iletilir.

Ayrıca press() ve release() metotları kullanılarak Shift, Ctrl gibi sürekli basılan tuşlar da desteklenmektedir.

5. Donanım ve Geliştirme Ortamı Bilgileri

Donanım: ESP32 Devkit v1

Yazılım Geliştirme Ortamı: Arduino IDE (ESP32 destekli)

Board Ayarları:

Board: "ESP32 Dev Module"

Upload Speed: 921600

Flash Frequency: 80MHz

Partition Scheme: Default

Seri İletişim Baud Rate: 115200

BLE Konfigürasyonları:

BLE yayın gücü: BLEDevice::setPower(ESP_PWR_LVL_P9) ile maksimum seviye

MTU değeri: 517 byte olarak ayarlanmış (yüksek veri aktarımı için)

Reklam yayın aralıkları: 0x20 (min) ve 0x40 (max) olarak belirlenmiştir

6. Test Süreci ve Karşılaşılan Zorluklar

Test: Farklı PS/2 klavyeler ile testler gerçekleştirilmiş ve BLE destekli cihazlara (Android telefon, Windows/Mac PC) bağlantı başarıyla sağlanmıştır.

Karşılaşılan Problemler:

Bazı eski klavyelerde tuş kodlarının beklenenden farklı olması

BLE bağlantısının nadiren kopması (çözüm: otomatik yeniden reklam başlatma)

Bazı özel karakterlerin (F1-F12 gibi) desteklenmemesi

İyileştirmeler:

Tuş kombinasyon desteği (Ctrl+C gibi)

Dil seçimi ve karakter eşlemeleri (Türkçe Q/F klavye)

Batarya ve güç tasarruf modlarının entegrasyonu

7. Sonuç ve Geliştirilebilir Alanlar

Bu proje, eski PS/2 klavyelerin yeniden kullanıma kazandırılması ve modern Bluetooth cihazlarla entegrasyonu için örnek teşkil etmektedir. Donanım bilgisi, yazılım geliştirme ve BLE protokol kullanımı bir arada deneyimlenmiştir.

İleriye Dönük Öneriler:

BLE üzerinden durum bilgisi aktarımı (örneğin LED ile bağlantı göstergesi)

Dahili batarya ile taşınabilirlik

USB üzerinden çift çıkış (hem BLE hem USB HID)

Klavye düzeni seçimi için fiziksel buton veya seri komut

8. Ek: Bağlantı Şeması ve Devre Diyagramı (İsteğe Bağlı Eklenebilir)

Bağlantılar:

PS/2 DATA → GPIO13 (ESP32)

PS/2 CLOCK → GPIO14 (ESP32)

5V → ESP32 VIN

GND → GND

Gerekli durumlarda seri port üzerinden hata ayıklama yapılabilir.

Kaynaklar:

https://github.com/espressif/arduino-esp32

https://github.com/T-vK/ESP32-BLE-Keyboard

https://github.com/PaulStoffregen/PS2Keyboard

https://www.bluetooth.com/specifications/specs/human-interface-device-profile-1-1/
