#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int rly = 17;

String dataIn = "";  // buffer untuk membaca data

void setup() {
  Serial.begin(115200);
  pinMode(rly, OUTPUT);
  digitalWrite(rly, LOW); // relay awal OFF

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with Bluetooth!");
}

void loop() {

  // --- Kirim data dari Serial ke Bluetooth ---
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // --- Baca data dari Bluetooth ---
  if (SerialBT.available()) {
    char c = SerialBT.read();
    dataIn += c;          // simpan karakter ke buffer
    Serial.print(c);      // tampilkan di Serial Monitor

    // Jika ada newline atau sudah lengkap
    if (c == '\n' || c == '\r') {
      dataIn.trim();      // hapus spasi/enter

      // --- CEK PERINTAH ---
      if (dataIn.equalsIgnoreCase("ON")) {
        digitalWrite(rly, LOW);
        Serial.println("Relay ON");
      }
      else if (dataIn.equalsIgnoreCase("OFF")) {
        digitalWrite(rly, HIGH);
        Serial.println("Relay OFF");
      }

      dataIn = ""; // reset buffer untuk input berikutnya
    }
  }

  delay(20);
}
