bool BL = 0;
byte cont = 1;
int nivel;
int temp;
#include <Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
  // put your setup code here, to run once:
  pinMode(2 , INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:
  nivel = map(analogRead(A0), 0, 1023, 0, 1000);
  temp = map(analogRead(A1), 0, 1023, 0, 200);
  //apertar botao liga
  if (cont == 1) {
    if (digitalRead(3) == LOW) {
      BL = 1;
      cont = 2;
    }
  }
  if (cont == 2) {
    if (BL == 1) {
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Tanque enchendo...");
      cont = 3;
    }
  }
  if (cont == 3) {
    if (nivel > 499) {
      digitalWrite(10, LOW);
      if (nivel > 799) {
        digitalWrite(11, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tanque cheio!");
        cont = 4;
      }
    }
  }
  if (cont == 4) {
    if (nivel > 800) {
      digitalWrite(7, HIGH);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Resistencia Ligada");
      lcd.setCursor(0, 1);
      lcd.print("Liquido Aquecendo...");
      delay(500);
      cont = 5;
    }
  }
  if (cont == 5) {
    temp = map(analogRead(A1), 0, 1023, 0, 200);
    if (temp > 79) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aquecimento Completo");
      lcd.setCursor(0, 1);
      lcd.print("Agitador Ligado");
      delay(700);
      lcd.clear();
      for (byte motor = 40; motor <= 100; motor = motor + 20) {
        temp = map(analogRead(A1), 0, 1023, 0, 200);
        analogWrite(6, motor);
        if (temp > 89) {
          digitalWrite(7, 0);
        }
        lcd.setCursor(0,0);
        lcd.print("Misturando produtos");
        delay(1000);
      }
      cont = 6;
    }
  }
  if (cont == 6) {
    delay(5000);
    digitalWrite(12, HIGH);
    digitalWrite(6,LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto finalizado!");
    cont = 7;
  }
  if (cont == 7) {
    if (digitalRead(2) == LOW) {
      BL = 0;
      cont = 1;
      digitalWrite(12, LOW);
      digitalWrite(7, LOW);
      lcd.clear();
    }
  }
}
