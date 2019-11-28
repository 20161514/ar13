/*
 예제 7.1
 스텝모터 구동
 */
 
// 스텝 모터 신호핀 설정
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
const int cwPin = 2; 
const int stopPin = 7; 
const int ccwPin = 4; 

  boolean cwCheck = false;
  boolean stopCheck = false;
  boolean ccwCheck = false;
// stop 구간 폭 설정
int stopRange = 100;


// 스텝 모터의 스텝 설정
// 0~7은 동작 신호, 8번째는 모터 정지 신호
int steps[] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001, B0000};

void setup() {
  //모터 신호핀을 출력으로 설정
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(cwPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(ccwPin, INPUT_PULLUP);

  // 시리얼 통신 설정  
  Serial.begin(9600);
}

void loop(){

  int cwInput = digitalRead(cwPin);
  int stopInput = digitalRead(stopPin);
  int ccwInput = digitalRead(ccwPin);

  if(cwInput == LOW) {
    cwCheck = true;
    stopCheck = false;
    ccwCheck = false;
  }
  else if(ccwInput == LOW) {
    ccwCheck = true;
    cwCheck = false;
    stopCheck = false;
  }
  else if(stopInput == LOW) {
      cwCheck = false;
    stopCheck = true;
    ccwCheck = false;
  }


  // CW로 회전시 모터를 CW방향으로 회전시킨다.
  if(cwCheck){
     Serial.println("CW Motor");     
    // CW로 회전시킨다.
    clockwise();
  }
  // CCW로 회전시 모터를 CCW방향으로 회전시킨다.
  else if(ccwCheck){
    Serial.println("CCW Motor");    
    // CCW로 회전시킨다.
    counterClockwise();
  }
  // 중간에 위치 했을 경우 정지시킨다.  
  else if(stopCheck) {
    Serial.println("Motor Stop");
    motorStop();
  }
}

void counterClockwise(){
  // 0~7 번째 신호를 순차적으로 출력시킨다.
  for(int i = 0; i < 8; i++)
  {
    motorSignalOutput(i);
    delayMicroseconds(1000);
	
  }
}

void clockwise(){
  // 7~0 번째 신호를 순차적으로 출력시킨다.
  for(int i = 7; i >= 0; i--)
  {
    motorSignalOutput(i);
    delayMicroseconds(1000);
  }
}

void motorStop(){
  // 정지신호를 출력시킨다.
  motorSignalOutput(8); 
}

void motorSignalOutput(int out)
{
  // out 변수에 해당하는 모터 시그날을 출력한다.
  digitalWrite(motorPin1, bitRead(steps[out], 0));
  digitalWrite(motorPin2, bitRead(steps[out], 1)); 
  digitalWrite(motorPin3, bitRead(steps[out], 2));
  digitalWrite(motorPin4, bitRead(steps[out], 3));
}
