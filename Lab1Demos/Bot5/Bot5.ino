/*Code for Robot 5: IR Robot
*When the left eye detects something, it will turn right
*Right eye: turn left
*Both eyes: back up
*/

#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(12);
  servoRight.attach(13);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  pinMode(10, INPUT); pinMode(11, OUTPUT); // Left IR LED and Receiver
  pinMode(3, INPUT); pinMode(2, OUTPUT); // Right IR LED and Receiver
  pinMode(7, OUTPUT); pinMode(8, OUTPUT); // Indicator LEDs

  Serial.begin(9600);
}

void loop() {
  int irLeft = irDetect(11, 10, 38000); // Check for objects on the left
  int irRight = irDetect(3, 2, 38000); // Check for objects on the right

  digitalWrite(8, !irLeft);
  digitalWrite(7, !irRight);
  react(irLeft, irRight);
}

int irDetect(int irLED, int irReceiver, long frequency) {
  tone(irLED, frequency, 8); // Send out a 38 kHz pulse for 1 ms
  delay(1);
  int ir = digitalRead(irReceiver); // If detected, return 0; else, return 1
  delay(1);
  return(ir);
}

void react(int irLeft, int irRight) {
  if (irLeft == 0 && irRight == 0) { // Object ahead
    goBackward();
    delay(1000);
    turnRight();
    delay(2000);
  }
    if (irLeft == 0 && irRight == 1) { // Object left
    turnRight();
    delay(200);
  }
    if (irLeft == 1 && irRight == 0) { // Object right
    turnLeft();
    delay(200);
  }
    if (irLeft == 1 && irRight == 1) { // No object
    goForward();
    delay(150);
  }
}

void goForward() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  return;
}

void goBackward() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  return;
}

void turnLeft() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  return;
}

void turnRight() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  return;
}
