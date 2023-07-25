/*
 *   3-Eksen Manyetometre Veri Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Manyetometre(Magne) sensöründen gelen X,Y,Z verileri okumaktadır ve seri port ekranına yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap 9-Eksen Ataletsel Ölçüm Birimi için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-9-eksen-ataletsel-olcum-biri <------
 *      ------> https://github.com/deneyapkart/deneyap-9-eksen-ataletsel-olcum-birimi-arduino-library <------
 *
 */
#include <Deneyap_9EksenAtaletselOlcumBirimi.h>                // Deneyap 9-Eksen Ataletsel Ölçüm Birimi kutuphanesi eklenmesi

MAGNETOMETER Magne;                                            // MAGNETOMETER icin Class tanimlamasi

void setup() {
    Serial.begin(115200);                                      // Seri haberleşme başlatılması
    if (!Magne.begin(0x60)) {                                  // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(2500);
        Serial.println("I2C bağlantısı başarısız ");           // I2C bağlantısı başarısız olursa seri terminale yazdırma
        while (1);
    }
}

void loop() {
    Magne.RegRead();
    Serial.print("X ekseni:");
    Serial.print(Magne.readMagnetometerX());                     // X-eksen manyetometre verisi okuma
    Serial.print("\tY ekseni:");
    Serial.print(Magne.readMagnetometerY());                     // Y-eksen manyetometre verisi okuma
    Serial.print("\tZ ekseni:");
    Serial.println(Magne.readMagnetometerZ());                   // Z-eksen manyetometre verisi okuma
    delay(1000);
}
