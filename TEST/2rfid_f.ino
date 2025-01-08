#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// RFID Reader 1
#define RST_PIN_1 9
#define SS_PIN_1 10
#define LED_PIN_1 5

// RFID Reader 2
#define RST_PIN_2 7
#define SS_PIN_2 8
#define LED_PIN_2 6

// Servo Motor
#define SERVO_PIN 3

MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_2);
Servo myServo;

byte correctUID[] = { 0xE2, 0x19, 0xB0, 0x24 };

bool isServoAtZero = true;

void setup() {
  Serial.begin(9600);
  SPI.begin();

  // Initialize RFID modules
  rfid1.PCD_Init();
  rfid2.PCD_Init();

  myServo.attach(SERVO_PIN);
  myServo.write(0); // Servo starts at initial position

  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  Serial.println("Place your RFID card near either reader.");
}

void loop() {
  // Check RFID Reader 1
  if (checkRFID(rfid1, SS_PIN_1, LED_PIN_1, "RFID Reader 1")) {
    toggleServoPosition();
  }

  // Check RFID Reader 2
  if (checkRFID(rfid2, SS_PIN_2, LED_PIN_2, "RFID Reader 2")) {
    toggleServoPosition();
  }
}

bool checkRFID(MFRC522 &rfid, int ssPin, int ledPin, const char *readerName) {
  // Activate RFID reader
  digitalWrite(ssPin, LOW);

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print(readerName);
    Serial.print(" Card UID: ");

    byte uidMatch = checkKey(rfid.uid.uidByte, rfid.uid.size);

    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    if (uidMatch) {
      Serial.println("Access Granted");
      digitalWrite(ledPin, HIGH); // Turn on corresponding LED
      delay(2000);                // Keep LED on for 2 seconds
      digitalWrite(ledPin, LOW);  // Turn off LED
      rfid.PICC_HaltA();          // Halt the card
      digitalWrite(ssPin, HIGH);  // Deactivate RFID reader
      return true;
    } else {
      Serial.println("Access Denied");
    }
  }

  // Ensure RFID reader is deactivated
  digitalWrite(ssPin, HIGH);
  return false;
}

byte checkKey(byte *uid, byte uidSize) {
  if (uidSize != sizeof(correctUID)) {
    return 0;
  }

  for (byte i = 0; i < uidSize; i++) {
    if (uid[i] != correctUID[i]) {
      return 0;
    }
  }

  return 1;
}

void toggleServoPosition() {
  if (isServoAtZero) {
    myServo.write(90); // Rotate to open
    isServoAtZero = false;
  } else {
    myServo.write(0);  // Rotate to close
    isServoAtZero = true;
  }
  delay(2000); // Allow servo movement to complete
}
