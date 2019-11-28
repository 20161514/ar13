/*
 예제 7.2
 서보모터 구동
*/
 
// 서보모터 라이브러리 불러오기
#include <Servo.h> 

// 서보모터 이름 설정
Servo motor1; 

// 서보 모터 신호핀 설정
int servoMotorPin = 9;
const int cwSw = 2;
const int ccwSw = 4;
// 모터 각도 변수 설정
int motorAngle;
int motorAngleOld;
int cwAngle = 180;
int ccwAngle = 0;
void setup() {
  
  // 서보모터 설정. 0.6ms 부터 2.4ms 범위로 설정
  motor1.attach(servoMotorPin, 600, 2400);
pinMode(cwSw, INPUT_PULLUP);
  pinMode(ccwSw, INPUT_PULLUP);
  // 시리얼 통신 설정  
  Serial.begin(9600);
}

void loop(){
 int cwInput = digitalRead(cwSw);
  int ccwInput = digitalRead(ccwSw);
  if(cwInput == LOW){
      motor1.write(cwAngle);
  }
  else if(ccwInput == LOW){
    motor1.write(ccwAngle);
  }


  // 이전각도와 현재 각도가 같지 않으면 시리얼 모니터에 각도를 출력한다.  
  if(motorAngle != motorAngleOld){
    Serial.print("Servo Motor Angle is: ");
    Serial.println(motorAngle);
  }

  // 현재의 모터 각도를 저장한다.
  motorAngleOld = motorAngle;
  
  delay(20);

}
