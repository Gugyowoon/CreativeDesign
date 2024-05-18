//0515 revised 
// Using deadband concept to reduce the mg90 jittering 
// Using for loop for smooth servo motor movement 
// Limiting  tilt angle to 10-170 for stability

#include <Servo.h>
#define PAN_PIN 9
#define TILT_PIN 10
#define INIT_PAN_ANGLE 92
#define INIT_TILT_ANGLE 140
Servo panServo;
Servo tiltServo;

int MinAngle = 100; // 모터 안정성을 위한 각도 제한 
int MinAngle_P = 0; 
int MaxAngle = 180; // 모터 안정성을 위한 각도 제한 
int MaxAngle_P = 180; 
int deadBand = 2; 
// ------------------------------------------------
void smoothServoMove(Servo& servo, int targetAngle, int step = 1, int stepDelay = 20){
  int currAngle = servo.read(); // 해당 시점의 각도값 기록 
  if(currAngle < targetAngle)
  {
    for(int angle = currAngle ; angle <= targetAngle ; angle+=step)
    {
      servo.write(angle); // step값 만큼 각도 서서히 증가
      delay(stepDelay); // 모터가 실제로 해당 각도까지 이동할 수 있도록 시간을 줌 
    }
  }
  else // currAngle >= targetAngle 
  {
    for (int angle = currAngle ; angle >= targetAngle ; angle-=step)
    {
      servo.write(angle);
      delay(stepDelay);
    }
  }
} 
// ------------------------------------------------
void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  panServo.attach(PAN_PIN); // 팬 서보 핀 설정 
  tiltServo.attach(TILT_PIN); // 틸트 서보 핀 설정 
    // Timer1 설정
  TCCR1A = 0;  // 레지스터 초기화
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 19999;  // 50Hz 주기 설정 (20ms 주기)

  TCCR1B |= (1 << WGM12);  // CTC 모드 설정
  TCCR1B |= (1 << CS11);   // 8 분주비 설정
  TIMSK1 |= (1 << OCIE1A); // 출력 비교 일치 인터럽트 활성화

  smoothServoMove(tiltServo, INIT_TILT_ANGLE, 1, 50);  // 지연 시간을 늘려 더 부드럽게 이동
  smoothServoMove(panServo, INIT_PAN_ANGLE, 1, 50);  // 지연 시간을 늘려 더 부드럽게 이동

}
// ------------------------------------------------

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read(); // input은 시리얼에서 읽어들인 명령어 
    int currentTiltAngle = tiltServo.read();
    int currentPanAngle = panServo.read();

    if (input == 'L') {
      // 왼쪽으로 이동, 각도 증가 , panAngle 90 -> 120 -> 150 -> 180 과 같이 변화함 
      smoothServoMove(panServo, min(MaxAngle_P, currentPanAngle + 30), 1, 3);  // 팬 서보를 오른쪽으로 30도 이동, 최대치는 MaxAngle_P
      
      Serial.print("Pan Angle: ");
      Serial.println(panServo.read());
    } 
    else if (input == 'R') {
      // 오른쪽으로 이동, 각도 감소 , panAngle 90 -> 60 -> 30 -> 0 과 같이 변화함 
      smoothServoMove(panServo, max(MinAngle_P, currentPanAngle - 30), 1, 3);  // 팬 서보를 왼쪽으로 30도 이동, 최소치는 MinAngle_P
      
      Serial.print("Pan Angle: ");
      Serial.println(panServo.read());
    }
    else if (input == 'U') {
      // 위로 이동, 각도 증가 
      smoothServoMove(tiltServo, currentTiltAngle + 20, 1, 20);  // 틸트 서보를 위로 30도 이동

      Serial.print("tilt Angle: ");
      Serial.println(tiltServo.read());
    }
    else if (input == 'D') {
        //  아래로 이동, 각도 감소 
      smoothServoMove(tiltServo, currentTiltAngle - 20, 1, 20);  // 틸트 서보를 아래로 30도 이동
      
      Serial.print("tilt Angle: ");
      Serial.println(tiltServo.read());
    }
    else
    {
      //Idle 
    }
  }
}

// AA
