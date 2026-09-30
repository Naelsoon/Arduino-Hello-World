#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED_1 19
#define LED_2 18
#define LED_3 5
#define LED_4 4
#define LED_5 2
#define BUTTON_1 35
#define BUTTON_2 32

bool semaforoAtivo = false; 

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 Pronto!");
}

void loop() {
  if (digitalRead(BUTTON_1) == HIGH) {
    semaforoAtivo = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Modo Semaforo");
  }

  if (digitalRead(BUTTON_2) == HIGH) {
    semaforoAtivo = false;
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Modo Semaforo");
    lcd.setCursor(0, 1);
    lcd.print("Desligado");
  }

  if (semaforoAtivo) {
    lcd.setCursor(0, 1);
    lcd.print("Sinal: VERDE   "); 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    delay(2000);

  
    if (digitalRead(BUTTON_2) == HIGH) return; 
    lcd.setCursor(0, 1);
    lcd.print("Sinal: AMARELO ");

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
    delay(1000);

    if (digitalRead(BUTTON_2) == HIGH) return;
    lcd.setCursor(0, 1);
    lcd.print("Sinal: VERMELHO");
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, HIGH);
    delay(2000);
  }
}
