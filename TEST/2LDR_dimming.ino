const int ldr1Pin = A0; // First LDR connected to analog pin A0
const int ldr2Pin = A1; // Second LDR connected to analog pin A1
const int pinkLEDPin = 9; // Pink LED connected to pin 9 (PWM)
const int purpleLEDPin = 10; // Purple LED connected to pin 10 (PWM)
 
void setup() {
  pinMode(pinkLEDPin, OUTPUT); // Set LED pins as output
  pinMode(purpleLEDPin, OUTPUT); // Set LED pins as output
  Serial.begin(9600); // Start Serial Monitor
}
 
void loop() {
  // Read the analog value from both LDRs
  int ldr1Value = analogRead(ldr1Pin);
  int ldr2Value = analogRead(ldr2Pin);
 
  // Invert the LDR values so that higher light levels result in dimmer LEDs
  // We subtract the LDR value from 1023 to invert the relation
  int pinkLEDBrightness = 1023 - ldr1Value; // Inverted brightness for LDR1
  int purpleLEDBrightness = 1023 - ldr2Value; // Inverted brightness for LDR2
 
  // Map the inverted LDR values to PWM range (0-255) for LED brightness
  pinkLEDBrightness = map(pinkLEDBrightness, 0, 1023, 0, 255);
  purpleLEDBrightness = map(purpleLEDBrightness, 0, 1023, 0, 255);
 
  // Write the brightness to the LEDs using PWM
  analogWrite(pinkLEDPin, pinkLEDBrightness);
  analogWrite(purpleLEDPin, purpleLEDBrightness);
 
  // Print LDR values and LED brightness to the Serial Monitor
  Serial.print("LDR1 Value: ");
  Serial.print(ldr1Value);
  Serial.print(" | Pink LED Brightness: ");
  Serial.print(pinkLEDBrightness);
  Serial.print(" | LDR2 Value: ");
  Serial.print(ldr2Value);
  Serial.print(" | Purple LED Brightness: ");
  Serial.println(purpleLEDBrightness);
 
  delay(100); // Short delay for faster responsiveness
}
 
