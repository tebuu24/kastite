#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define RST_PIN 9
#define SS_PIN 10
#define LED_PIN 7
#define SERVO_PIN 3
 
MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;
 
byte correctUID[] = { 0xE6, 0x71, 0x7A, 0x59 };
 
bool isAtZero = true;
 
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  myServo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Place your RFID card near the reader");
  myServo.write(0);
}
 
void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
 
  Serial.print("Card UID:");
  byte uidMatch = checkKey(rfid.uid.uidByte, rfid.uid.size);
 
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
 
  Serial.println();
 
  if (uidMatch) {
    Serial.println("Access Granted");
    toggleServoPosition();
  } else {
    Serial.println("Access Denied");
  }
 
  rfid.PICC_HaltA();
}
 
byte checkKey(byte* uid, byte uidSize) {
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
  digitalWrite(LED_PIN, HIGH);
 
  if (isAtZero) {
    myServo.write(90);
    isAtZero = false;
  } else {
    myServo.write(0);
    isAtZero = true;
  }
 
  delay(2000);
 
  digitalWrite(LED_PIN, LOW);
}
