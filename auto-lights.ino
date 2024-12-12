/*

  Auto-lights is a basic project to turn automatically my room's light, using a motor to toggle the switch.
  I could use a relay, but I think it's cooler to watch the motor idk.

*/
#include <Servo.h>

const int trigPin = 9; // Pin connected to the trigger (ultrasonar sensor)
const int echoPin = 10;
float duration, distance;
bool pastStateMotor = true; // Starts with the lights on
Servo motorSwitch;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motorSwitch.attach(8);
  Serial.begin(9600);
}

void switcher (int action) {
  // 1 = ON 
  // 0 = OFF
  int deviation = 20; // Because the rotary element isn't right on the 0 degrees.
  int pointZero = 90 + deviation; // 90 degrees + 20 of deviation
  int pointOn = pointZero - 45;
  int pointOff = pointZero + 45;

  delay(500);

  motorSwitch.write(pointZero); // In case we don't know what was the last position.
 
  delay(500); // Delay before rotation

  switch (action) {
    case 1:
      motorSwitch.write(pointOn);
      break;
    case 0:
      motorSwitch.write(pointOff);
      break;
    default:
      break;
  }

  delay(500); // Delay before returning to start point.
  motorSwitch.write(pointZero); // Return to start point after toggling ON/OFF.
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
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20) { // If we pass the hand right above the sensor
    if (pastStateMotor == true) { // If the past action was ON
      switcher(0); // Turn the lights off
      pastStateMotor = false; // Set the flag to false
    } else if (pastStateMotor == false) { // If the past action was OFF
      switcher(1); // Turn the lights on
      pastStateMotor = true; // Set the flag to true
    }
  }
}
