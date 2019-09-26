#include <LiquidCrystal_I2C.h>
#include<Wire.h>
int blinkNumber = 0;
LiquidCrystal_I2C lcd(0x27,16,2); //LCD 클래스 초기화, 0x3F

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available()) {
  char val = Serial.read();
  if (isDigit(val)) {
    blinkNumber = (val - '0');
  }
  for(char i = 0; i < blinkNumber; i++) {
    lcd.noBacklight();
    delay(250);
  lcd.backlight();
  delay(250);
  }
lcd.print("blinkTime");
lcd.setCursor(0,1);
lcd.print(blinkNumber);
}
}

