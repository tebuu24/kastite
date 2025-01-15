#include <Servo.h>

// Define pins for LDRs and servo
const int ldr1Pin = A0; // First LDR connected to analog pin A0
const int ldr2Pin = A1; // Second LDR connected to analog pin A1
const int servoPin = 3; // Servo motor connected to pin 3 (PWM)

// Initialize servo object
Servo myServo;

// Define threshold values for LDRs
const int ldr1Threshold = 600; // Example threshold for LDR1
const int ldr2Threshold = 600; // Example threshold for LDR2

// Track the current position of the servo
bool isAtZero = true;

void setup() {
  // Initialize servo
  myServo.attach(servoPin);
  myServo.write(90); // Start at neutral position

  // Initialize serial communication
  Serial.begin(9600);

  // Print initial message
  Serial.println("Monitoring light sensors...");
}

void loop() {
  // Read the analog values from both LDRs
  int ldr1Value = analogRead(ldr1Pin);
  int ldr2Value = analogRead(ldr2Pin);

  // Print LDR values to Serial Monitor
  Serial.print("LDR1 Value: ");
  Serial.print(ldr1Value);
  Serial.print(" | LDR2 Value: ");
  Serial.println(ldr2Value);

  // Check if LDR1 exceeds its threshold
  if (ldr1Value >= ldr1Threshold && !isAtZero) {
    myServo.write(0); // Turn servo to 0 degrees
    isAtZero = true;
    Serial.println("LDR1 triggered: Servo at 0 degrees.");
  }

  // Check if LDR2 exceeds its threshold
  if (ldr2Value >= ldr2Threshold && isAtZero) {
    myServo.write(180); // Turn servo to 180 degrees
    isAtZero = false;
    Serial.println("LDR2 triggered: Servo at 180 degrees.");
  }

  // Short delay for responsiveness
  delay(100);
}
