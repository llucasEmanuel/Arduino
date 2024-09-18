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
void SemaCar::print_count(LiquidCrystal &lcd) {
  unsigned long time_elapsed = millis() - start_green;
  if (is_counting && time_elapsed > 12000 && time_elapsed < 32000) {
    int num = time_elapsed/1000;
    int count = 32 - num;
    char msg[17];
    lcd.setCursor(0, 0);
    lcd.print("=TEMPO RESTANTE=");
    lcd.setCursor(0, 1);
    sprintf(msg, "     %02d seg     ", count);
    lcd.print(msg);
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
    is_counting = false;
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
void SemaCar::work(LiquidCrystal &lcd) {
  check_button();
  handle_green();
  handle_yellow();
  handle_red();
  print_count(lcd);
  restart();
}
