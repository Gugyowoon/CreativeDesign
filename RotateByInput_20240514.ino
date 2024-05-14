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
     if (input == 'l') 
    {  // 왼쪽으로 이동
        panAngle = min(170, panAngle + 30);  // 최대 각도는 170
        panServo.attach(9);
        panServo.write(panAngle);
        delay(200);
        int servoAngle_p = panServo.read();  // 서보모터의 현재 각도 읽기
        Serial.print("Pan Angle: ");
        Serial.println(servoAngle_p);
        panServo.detach(); // 모터 연결 해제 ; Jitter 방지 
    
    /*
    { 
      if(panAngle<154) //3번 L입력 전까지는 계속 회전받고 
      {
        for(int i=1; i<31; i++)
        {
          panServo.attach(9);
          //panAngle = ;  // panAngle 최대값은 170
          panServo.write(min(170, panAngle + i));
          delay(10); //0.01 sec ; 총 30도 이동에 0.3sec 소요 
          panServo.detach();
        }
        panAngle = min(170, panAngle + 30); // 여기서 panAngle이 170(MAX)되고 나면 더 이상 회전 없음 
      }
      
      int servoAngle_p = panServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("Pan Angle: ");
      Serial.println(servoAngle_p);
    
    */
    } 

    else if (input == 'r') 
    { // 오른쪽으로 이동
      panAngle = max(10, panAngle - 30);  // 최소 각도는 10
      panServo.write(panAngle);
      delay(200);
      int servoAngle_p = panServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("Pan Angle: ");
      Serial.println(servoAngle_p);
      panServo.detach(); // 모터 연결 해제 ; Jitter 방지 
    }

    
    else if (input == 'u') 
    { // 위로 이동
      tiltAngle = min(170, tiltAngle + 22);  // 최대 각도 170
      tiltServo.write(tiltAngle);
      int servoAngle_t = tiltServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("tilt Angle: ");
      Serial.println(servoAngle_t);
      delay(100);
    }
    else if (input == 'd') 
    {    //  아래로 이동
      tiltAngle = max(10, tiltAngle - 22);  // 최소 각도는 10도
      tiltServo.write(tiltAngle);
      int servoAngle_t = tiltServo.read();  // 서보모터의 현재 각도 읽기
      Serial.print("tilt Angle: ");
      Serial.println(servoAngle_t);
      delay(100);
      
    }
  }
}
