#include <Arduino.h>
#include "sema_car.h"
#include "ports.h"

// Gerencia quando o verde será aceso
void SemaCar::handle_green() {
  // Checa se está no meio de um ciclo
  if (is_counting) {
    // Checa se o ciclo está no intervalo (0s - 10s)
    if (millis() - start_green < 10000)
      digitalWrite(GREEN, HIGH);
    // Se sair desse intervalo, o verde desliga
    else
      digitalWrite(GREEN, LOW); 
  } 
  // Se o botão não for pressionado, o sinal fica verde para sempre
  else {
    digitalWrite(GREEN, HIGH);
  }
}

// Gerencia quando o amarelo é aceso
void SemaCar::handle_yellow() {
  // Checa se está no meio de um ciclo
  if (is_counting) {
    // Checa se o ciclo está no intervalo (10s - 12s)
    if (millis() - start_yellow > 10000 && millis() - start_yellow < 12000)
      digitalWrite(YELLOW, HIGH);
    // Se sair desse intervalo, o amarelo desliga
    else
      digitalWrite(YELLOW, LOW); 
  }
  // Se o botão não for pressionado, nunca fica amarelo
  else {
    digitalWrite(YELLOW, LOW);
  }
}

// Gerencia quando o vermelho é aceso
void SemaCar::handle_red() {
  // Checa se está no meio de um ciclo
  if (is_counting) {
    // Checa se o ciclo está no intervalo (12s - 32s)
    if (millis() - start_red > 12000 && millis() - start_red < 32000)
      digitalWrite(RED, HIGH);
    // Se sair desse intervalo, o vermelho desliga
    else
      digitalWrite(RED, LOW);  
  }
  // Se botão não for pressionado, nunca fica vermelho
  else {
    digitalWrite(RED, LOW);
  }
}

// Printa o contador no display LCD
void SemaCar::print_count(LiquidCrystal lcd) {
  if (is_counting && digitalRead(RED) == HIGH) {
    lcd.setCursor(0, 0);
    // Serial.println((millis() - start_green)/1000);
    lcd.print(32 - (millis() - start_green)/1000);
    // Arrumar uma forma de tirar o 0 da direita do número quando chega no 9
  }
  else
    lcd.clear();
}

// Reseta as variáveis do ciclo
void SemaCar::restart() {
  // Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia o ciclo
  if (is_counting && millis() - start_red > 32000) {
    start_green = millis();
    start_yellow = millis();
    start_red = millis();
    /* if (is_counting) */ is_counting = false;
  }
}

// Inicializar cada variável de início de cada cor
SemaCar::SemaCar() {
  start_green = millis();
  start_yellow = millis();
  start_red = millis();
  is_counting = false;
}

void SemaCar::check_button() {
  // Se o botão for apertado (Adicionar condicial para checar se resetou o ciclo)
  if (digitalRead(BUTTON) == 0 && !is_counting) {
    start_green = millis();
    start_yellow = millis();
    start_red = millis();
    is_counting = true;
  }
}

// Método geral que executa o ciclo do semáforo dos carros
void SemaCar::work(LiquidCrystal lcd) {
  check_button();
  handle_green();
  handle_yellow();
  handle_red();
  print_count(lcd);
  restart();
}
