const int trigPin = 13;  // Trig pin connected to GPIO 13
const int echoPin = 12;  // Echo pin connected to GPIO 12

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Triggering the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reading the echo pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculating distance in centimeters
  // Speed of sound is approximately 343 meters per second (34,300 cm/s)
  // Formula: Distance = (Duration * Speed of Sound) / 2
  int distance_cm = (duration * 0.0343) / 2;

  // Print the distance to the Serial Monitor
  // Serial.print("Distance: ");
  Serial.println(distance_cm);
  // Serial.println(" cm");

  // Wait for a short time before the next measurement
  delay(1000);
}
