/*
 *   9-Eksen AccGyroMagne Veri Okuma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Sensörlerden gelen İvmeölçerden(Acc) X,Y,Z Dönüölçerden(Gyro) X,Y,Z, Manyetometre(Magne) X,Y,Z ve Sıcaklık C ve F cinsinden sıcaklık değerlerini
 *   seri port ekranına yazdırmaktadır.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap 9-Eksen Ataletsel Ölçüm Birimi için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-9-eksen-ataletsel-olcum-biri <------
 *      ------> https://github.com/deneyapkart/deneyap-9-eksen-ataletsel-olcum-birimi-arduino-library <------
 */
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>                // Deneyap 6-Eksen Ataletsel Ölçüm Birimi kutuphanesi eklenmesi
#include <Deneyap_9EksenAtaletselOlcumBirimi.h>                // Deneyap 9-Eksen Ataletsel Ölçüm Birimi kutuphanesi eklenmesi

LSM6DSM AccGyro;                                               // LSM6DSM icin Class tanimlamasi
MAGNETOMETER Magne;                                            // MAGNETOMETER icin Class tanimlamasi

void setup() {
    Serial.begin(115200);                                      // Seri haberleşme başlatılması
    AccGyro.begin(0x6B);                                       // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
    Magne.begin(0x60);                                         // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
}

void loop() {
    Serial.println("\nAkselerometre degerleri");
    Serial.print("X ekseni: ");                                  // X-eksen akselerometre verisi okuma
    Serial.print(AccGyro.readFloatAccelX());
    Serial.print("\tY ekseni: ");                                // Y-eksen akselerometre verisi okuma
    Serial.print(AccGyro.readFloatAccelY());
    Serial.print("\tZ ekseni: ");                                // Z-eksen akselerometre verisi okuma
    Serial.println(AccGyro.readFloatAccelZ());
    delay(500);

    Serial.println("\nGyro degerleri");
    Serial.print("X ekseni: ");                                  // X-eksen gyro verisi okuma
    Serial.print(AccGyro.readFloatGyroX());
    Serial.print("\tY ekseni: ");                                // Y-eksen gyro verisi okuma
    Serial.print(AccGyro.readFloatGyroY());
    Serial.print("\tZ ekseni: ");                                // Z-eksen gyro verisi okuma
    Serial.println(AccGyro.readFloatGyroZ());
    delay(500);

    Serial.println("\nMagnetometre degerleri");
    Serial.print("X ekseni:");
    Serial.print(Magne.readMagnetometerX());                     // X-eksen manyetometre verisi okuma
    Serial.print("\tY ekseni:");
    Serial.print(Magne.readMagnetometerY());                     // Y-eksen manyetometre verisi okuma
    Serial.print("\tZ ekseni:");
    Serial.println(Magne.readMagnetometerZ());                   // Z-eksen manyetometre verisi okuma
    delay(500);

    Serial.println("\nSicaklik degerleri");
    Serial.print("Celsius: ");                                   // Sicaklik verisi okuma (Celsius)
    Serial.print(AccGyro.readTempC());
    Serial.print("\tFahrenheit: ");                              // Sicaklik verisi okuma (Fahrenheit)
    Serial.println(AccGyro.readTempF());
    delay(500);
}
