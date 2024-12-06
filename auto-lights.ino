/*

  Auto-lights is a basic project to turn automatically my room's light, using a motor to toggle the switch.
  I could use a relay, but I think it's cooler to watch the motor idk.

*/

const int trigPin = 9; // Pin connected to the trigger (ultrasonar sensor)
const int echoPin = 10;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  if (distance < 20) {
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  delay(100);
}
