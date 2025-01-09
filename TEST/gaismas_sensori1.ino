// Setup pins and variables
const int sensor1Pin = A0;
const int sensor2Pin = A1;
const int led1Pin = 5;
const int led2Pin = 7;

void setup() {
  // Initialize pins
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int sensor1Value = analogRead(sensor1Pin);
  int sensor2Value = analogRead(sensor2Pin);

  // Print sensor readings to Serial Monitor
  Serial.print("Sensor 1: ");
  Serial.println(sensor1Value);
  Serial.print("Sensor 2: ");
  Serial.println(sensor2Value);

  // Add 100 to readings
  int sensor1Threshold = sensor1Value + 70;
  int sensor2Threshold = sensor2Value + 70;

  // Compare sensor values
  if (sensor1Value >= sensor1Threshold) {
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }

  if (sensor2Value >= sensor2Threshold) {
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
  }

  // Delay for periodic reading
  delay(500);
}
