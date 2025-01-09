#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_2 7
#define SS_PIN_2 8
#define LED_PIN_2 6

MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid2.PCD_Init();
  pinMode(LED_PIN_2, OUTPUT);
  Serial.println("Place your RFID card near RFID Reader 2.");
}

void loop() {
  if (checkRFID(rfid2, SS_PIN_2, LED_PIN_2, "RFID Reader 2")) {}
}

bool checkRFID(MFRC522 &rfid, int ssPin, int ledPin, const char *readerName) {
  digitalWrite(ssPin, LOW);
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print(readerName);
    Serial.print(" Card UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    Serial.println("Access Granted");
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    rfid.PICC_HaltA();
    digitalWrite(ssPin, HIGH);
    return true;
  }
  digitalWrite(ssPin, HIGH);
  return false;
}
