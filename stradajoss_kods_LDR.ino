#include <Servo.h>

//Definē LDR, LED un servomotora pieslēgvietas (labais LRD ir LDR1 un kreisais ir LDR2)
const int ldr1Pin = A0;
const int ldr2Pin = A1;
const int servoPin = 6;
//Rozā un zilās LED savienojam vienā pin9
const int led1Pin = 9;
const int led2Pin = 10;

//Izveido servomotora objektu
Servo myServo;

//Saglabā pašreizējo servomotora pozīciju
int currentPosition = 90;

void setup() {
  //Pieslēdz servomotoru un iestata sākuma pozīciju
  myServo.attach(servoPin);
  myServo.write(currentPosition);

  //Iestata LED kā izejas pieslēgvietas
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  //Inicializē seriālo komunikāciju, lai veiktu testēšanu, vienkāŗšotu atkļūdošanu
  Serial.begin(9600);
  Serial.println("Uzrauga gaismas sensorus...");
}

void loop() {
  //nolasa analogo vērtību no abiem LDR sensoriem
  int ldr1Value = analogRead(ldr1Pin);
  int ldr2Value = analogRead(ldr2Pin);

  //Definē LDR sliekšņa vērtības (no testēšanas šī vērtība ir optimāla)
  int ldr1Threshold = 650;
  int ldr2Threshold = 650;

  //Izvada LDR vērtības uz seriālo monitoru
  Serial.print("LDR1 Vērtība: ");
  Serial.print(ldr1Value);
  Serial.print(" | LDR2 Vērtība: ");
  Serial.println(ldr2Value);

  //Ja LDR1 pārsniedz slieksni un pašreizējā pozīcija nav 0, pārvieto servo par
  if (ldr1Value >= ldr1Threshold && currentPosition != 0 && ldr1Value > ldr2Value) {
    currentPosition = 0;
    myServo.write(currentPosition);
    analogWrite(led1Pin, 255);
    analogWrite(led2Pin, 0);
    Serial.println("LDR1 aktivizēts: Servo 0 grādos un LED1 ieslēgts.");
  }

  //Ja LDR2 pārsniedz slieksni un pašreizējā pozīcija nav 90, pārvieto servo
  if (ldr2Value >= ldr2Threshold && currentPosition != 90 && ldr2Value > ldr1Value) {
    currentPosition = 90;
    myServo.write(currentPosition);
    analogWrite(led2Pin, 255);
    analogWrite(led1Pin, 0);
    Serial.println("LDR2 aktivizēts: Servo 90 grādos un LED2 ieslēgts.");
  }

  delay(100);
}
