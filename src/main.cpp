#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DETECTOR_PIN 2
#define ACTIVATION_PIN 3

int counter = 0;
int state = HIGH;

void setup() {
  pinMode(DETECTOR_PIN, INPUT);
  pinMode(ACTIVATION_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(" Obstacle Avoidance");

  digitalWrite(ACTIVATION_PIN, state);

  lcd.setCursor(0, 1);
  lcd.print("ENABLED");

  lcd.setCursor(0, 3);
  lcd.print("Counter: 0");
}

void loop() {
  if (state == LOW) {
    counter++;

    lcd.setCursor(9, 3);
    lcd.print(counter);

    if (counter == 100) {
      state = HIGH;
      counter = 0;
      digitalWrite(ACTIVATION_PIN, state);

      lcd.setCursor(0, 1);
      lcd.print("ENABLED ");

      lcd.setCursor(9, 3);
      lcd.print("0  ");
    }
  }

  int blocked = digitalRead(DETECTOR_PIN);

  lcd.setCursor(0, 2);

  if (blocked == LOW) {
    lcd.print("blocked");
    state = LOW;
    digitalWrite(ACTIVATION_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("DISABLED");
  } else {
    if (state == HIGH) {
      lcd.print("free   ");
    }
  }

  delay(100);
}
