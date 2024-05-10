#include <Servo.h>
#define SERVO_PIN 10

Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN); // Replace SERVO_PIN with the pin connected to your servo
}

void loop() {
  // Calibrate to 0 degrees
  myServo.writeMicroseconds(1500); // Start with a centered position
  // myServo.write(90);
  // Fine-tune if needed
  // myServo.writeMicroseconds(1450); // Example of fine-tuning
  
  delay(1000); // Delay to allow the servo to move
}
