#include <Servo.h>

Servo panServo;
Servo tiltServo;

int panAngle = 93;  // 초기 각도
int tiltAngle = 90;  // 초기 각도

void setup() {
  Serial.begin(9600);
  panServo.attach(9);
  tiltServo.attach(10);
  panServo.write(panAngle);  // 초기 각도로 설정
  tiltServo.write(tiltAngle);  // 초기 각도로 설정
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == 'l') {
      // 왼쪽으로 이동
      panAngle = max(0, panAngle + 30);  // 최소 각도는 0도
      panServo.write(panAngle);
      int servoAngle_p = panServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("Pan Angle: ");
      Serial.println(servoAngle_p);
      delay(100);
    } else if (input == 'r') {
      // 오른쪽으로 이동
      panAngle = min(180, panAngle - 30);  // 최대 각도는 180도
      panServo.write(panAngle);
      int servoAngle_p = panServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("Pan Angle: ");
      Serial.println(servoAngle_p);
      delay(100);
    }
    else if (input == 'u') {
      // 위로 이동
      tiltAngle = max(0, tiltAngle + 22);  // 최소 각도는 0도
      tiltServo.write(tiltAngle);
      int servoAngle_t = tiltServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("tilt Angle: ");
      Serial.println(servoAngle_t);
      delay(100);
    }
    else if (input == 'd') {
        //  아래로 이동
      tiltAngle = min(180, tiltAngle - 22);  // 최대 각도는 180도
      tiltServo.write(tiltAngle);
      int servoAngle_t = tiltServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("tilt Angle: ");
      Serial.println(servoAngle_t);
      delay(100);
      
    }
  }
}
