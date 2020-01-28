/*Code for Robot 1: RFID Robot
*This robot uses an RFID scanner to read tags.
*Based on the tag, it will either play a tone,
*or move in a certain direction.
*/

#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int val {0};
char code[0];
int bytesread {0};

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

}

void loop() {
  if(Serial.available() > 0) { // if data found
    if((val = Serial.read()) == 10) { // check for header
      bytesread = 0;
      while(bytesread < 10) { // read 10 digit code
        if(Serial.available() > 0) {
          val = Serial.read();
          if((val == 10) || (val == 13)) { // if header or ed
            break;
          }
          code[bytesread] = val; // add the code
          bytesread ++;
        }
      }
      if(bytesread == 10) {
        String codestring = String(code);
        Serial.println("TAG code is: ");
        Serial.println(code[9]);
        switch(code[9]) {
          case '2': // Sound
            tone(4, 466, 3000);
            break;
           case 'C': // Forward
            servoLeft.attach(13);
            servoRight.attach(12);
            servoLeft.writeMicroseconds(1700);
            servoRight.writeMicroseconds(1300);
            delay(1500);
            servoLeft.detach();
            servoRight.detach();
            break;
           case '9': // Back
            servoLeft.attach(13);
            servoRight.attach(12);
            servoLeft.writeMicroseconds(1300);
            servoRight.writeMicroseconds(1700);
            delay(1500);
            servoLeft.detach();
            servoRight.detach();
            break;
           case '7': // Right
            servoLeft.attach(13);
            servoRight.attach(12);
            servoLeft.writeMicroseconds(1300);
            servoRight.writeMicroseconds(1300);
            delay(1500);
            servoLeft.detach();
            servoRight.detach();
            break;
           case 'F': // Left
            servoLeft.attach(13);
            servoRight.attach(12);
            servoLeft.writeMicroseconds(1700);
            servoRight.writeMicroseconds(1700);
            delay(1500);
            servoLeft.detach();
            servoRight.detach();
            break;
        }
        bytesread = 0;
        digitalWrite(2, HIGH); // Reset the RFID
        delay(3000);
        digitalWrite(2, LOW); // Turn it back on
      }
    }
  }
}
