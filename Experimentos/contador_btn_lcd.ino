#include <LiquidCrystal.h>

const int rs = 12, e = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int btn = 10;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
unsigned long start = millis();
int count;
bool flag = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  int value = digitalRead(btn);

  lcd.setCursor(0, 0);

  if(value == LOW && flag == false) {
    flag = true;
    count = 10;
    start = millis();
    lcd.clear();
  }
  if(flag == true) {
    // conta até 1s
    if((millis() - start) > 1000) {
      start = millis();
      lcd.clear();
      count--;
    }
    lcd.print(count);
  }
  if(count == 0 && flag == true) {
    flag = false;
    lcd.clear();
    lcd.print("AAAAAAAAAAAAAAA");
  }
  
}
