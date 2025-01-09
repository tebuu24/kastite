#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 10
#define LED_PIN_1 5

#define RST_PIN_2 7
#define SS_PIN_2 8
#define LED_PIN_2 6

MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_2);

unsigned long lastSwitchTime = 0;
const unsigned long switchInterval = 500;
bool isReader1Active = true;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid1.PCD_Init();
  rfid2.PCD_Init();
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);

  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_2, HIGH);

  Serial.println("Place your RFID card near a reader.");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSwitchTime >= switchInterval) {
    lastSwitchTime = currentTime;
    isReader1Active = !isReader1Active;

    if (isReader1Active) {
      activateReader(rfid1, SS_PIN_1, "RFID Reader 1");
      deactivateReader(rfid2, SS_PIN_2, "RFID Reader 2");
    } else {
      activateReader(rfid2, SS_PIN_2, "RFID Reader 2");
      deactivateReader(rfid1, SS_PIN_1, "RFID Reader 1");
    }
  }

  // Check the currently active reader
  if (isReader1Active) {
    checkRFID(rfid1, LED_PIN_1, "RFID Reader 1");
  } else {
    checkRFID(rfid2, LED_PIN_2, "RFID Reader 2");
  }
}

void activateReader(MFRC522 &rfid, int ssPin, const char *readerName) {
  digitalWrite(ssPin, LOW);
  Serial.print(readerName);
  Serial.println(" activated.");
}

void deactivateReader(MFRC522 &rfid, int ssPin, const char *readerName) {
  digitalWrite(ssPin, HIGH);
  Serial.print(readerName);
  Serial.println(" deactivated.");
}

void checkRFID(MFRC522 &rfid, int ledPin, const char *readerName) {
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
  }
}
