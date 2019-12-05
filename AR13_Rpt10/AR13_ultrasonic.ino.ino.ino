/*
 예제 6.7
 초음파 거리센서를 이용한 거리 측정
*/

// 트리거 핀과 에코 핀 번호를 설정한다.
const char trigPin = 13;
const char echoPin = 12;
const int  yelloPin = 2;
const int  greenPin = 3;
const int  redPin = 4;
// 펄스 폭과 거리 변수 설정  
int pulseWidth;
int distance;
int distanceOld;
  
void setup() {
  // 시리얼 통신 설정
  Serial.begin (9600);
  // 트리거 핀은 출력으로, 에코핀은 입력으로 설정
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
pinMode(yelloPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(redPin, OUTPUT); 
  // 트리거 핀의 초기값을 LOW로 한다
  digitalWrite(trigPin, LOW);
}

void loop(){
  // 10us의 트리거 신호를 HC-SR04로 내보낸다.
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
  

  // Echo 펄스 폭을 측정하여 pulseWidth 변수에 저장한다.  
  pulseWidth = pulseIn(echoPin, HIGH);
  // 거리를 계산한다.
  distance = pulseWidth / 58;  

  // 감지거리인 2~200cm 범위의 거리값만 사용한다.
  if(distance <= 200 && distance >= 2){  
    // 이전의 거리값과 비교하여 변화가 있을 경우에만 
    // 시리얼 통신으로 전송한다.    
    if(distance <= 30 && distance >=2){
      digitalWrite(yelloPin,HIGH);
      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,LOW);
    }
    else if(distance <= 60 && distance >=31){
      digitalWrite(yelloPin,LOW);
      digitalWrite(greenPin,HIGH);
      digitalWrite(redPin,LOW);
    }
    else{
      digitalWrite(yelloPin,LOW);
      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,HIGH);
    }
    if(distance != distanceOld){
      Serial.print(distance);
      Serial.println(" cm");    
    };
  };
  distanceOld = distance;
  delay(100);
}
