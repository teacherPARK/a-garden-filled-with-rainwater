
#include <Servo.h>
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C_Hangul.h>
#include <Wire.h>
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 3;
char keys [ROWS][COLS] = {
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'},
};
  byte rowPins[ROWS] = {8,7,6,5};
  byte colPins[COLS] = {4,3,2};
  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
  int AA = 0;
  int AB = 1;
  int LED_R = 11;
  int LED_G = 12;
  int LED_B = 13;
  int rainigPin = A1;
  int servoPin = 9;
  Servo cover;
  int angle = 0;
  char key = 0;
  int NUM = 0;


void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  lcd.init();
  lcd.backlight();
  cover.attach(servoPin);  

 for(NUM=0;NUM<10;) {
    char key = keypad.getKey();
    NUM = key*10-480;
      if(NUM>0) {
    lcd.setCursor(1,0);
    lcd.print(NUM);
      if(NUM>=10){break;
      }
 }
}
}

void loop() {
  int value = analogRead(A1);
  int data = analogRead(A0);
  int percent = map(data, 1023, 210, 0, 100);
  lcd.setCursor(1,0);
  lcd.print("Moisture");
  lcd.setCursor(1,1);
  lcd.print(percent);
  lcd.print("%");
  lcd.setCursor(11,0);
  lcd.print("Goal");
  lcd.setCursor(11,1);
  lcd.print(NUM);
  delay(500);     
  
  if(percent>=NUM){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);  
}
              
 else{
   digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(AA, HIGH);
  digitalWrite(AB, LOW);
  delay(2000);
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
  delay(1000);
  }

   if (value<500) {
  cover.write(90);
  }
  else {
    cover.write(0);
  }   
}
