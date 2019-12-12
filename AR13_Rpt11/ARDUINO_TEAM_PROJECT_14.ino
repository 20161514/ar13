#include <Stepper.h>


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// 0번 아날로그핀을 CdS 셀 입력으로 설정한다.
const int CdSPin = 0;
boolean flag;
boolean swState;
const int stepValue = 1024;
Stepper myStepper(stepValue,11,9,10,8); 
const int switchPin = 2;

void setup() {
// 16X2 LCD 모듈 설정하고 백라이트를 켠다.
  lcd.init(); // LCD 설정
  lcd.backlight();
pinMode(switchPin, INPUT_PULLUP);
// 메세지를 표시한다.
  lcd.print("Arduino Project");
  lcd.setCursor(0,1);
  lcd.print("Team 14");
// 3초동안 메세지를 표시한다.
  delay(3000);

// 모든 메세지를 삭체한 뒤
// 숫자를 제외한 부분들을 미리 출력시킨다.
flag = false;
swState = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Illuminance:");
  lcd.setCursor(0,1);
  lcd.print("Blind status:");
  myStepper.setSpeed(30); 
  Serial.begin(9600); 
}

void loop(){
  int adcValue; // 실제 센서로부터 읽은 값 (0~1023)
  int illuminance; // 현재의 밝기. 0~100%
  adcValue = analogRead(CdSPin);
  illuminance = map(adcValue, 0, 1023, 100, 0);
  int swPut = digitalRead(switchPin);
  
  if(swState == false && swPut == LOW) {
    swState = true;
  }
  else if(swState == true && swPut == LOW) {
    swState = false;
  }
  



if(swState == false) {
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Illuminance:"); 
lcd.setCursor(0,1);
lcd.print("Blind status:");

lcd.setCursor(12,0);
lcd.print("   ");
lcd.setCursor(12,0);
lcd.print(illuminance);

delay(500);  
  if(!flag) {
    
    if(illuminance > 35) {
      blindUp();
    }
  }
  else{ 
    if(illuminance < 20){
      blindDown();
    }
  }
 }
else {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" IOT SYSTEM OFF ");
  delay(1000);
}
    
}

void blindUp() {
    Serial.println("counterclockwise");
     lcd.setCursor(13,1);
lcd.print("   ");
     lcd.setCursor(13,1);
  lcd.print("off");
    myStepper.step(10*stepValue);
    flag = true;
    delay(1000);
  }
void blindDown() {
   Serial.println("clockwise");
    lcd.setCursor(13,1);
lcd.print("   ");
    lcd.setCursor(13,1);
  lcd.print("on");
   myStepper.step(-10*stepValue);
   flag = false;
   delay(1000); 
  }


