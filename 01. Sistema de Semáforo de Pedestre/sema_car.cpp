#include <Arduino.h>
#include "sema_car.h"
#include "ports.h"

// Gerencia quando o verde será aceso
void SemaCar::handle_green() {
  // Checa se o ciclo está no intervalo (0s - 10s)
  if (millis() - start_green < 10000)
    digitalWrite(GREEN, HIGH);
  // Se sair desse intervalo, o verde desliga
  else
    digitalWrite(GREEN, LOW);  
}

// Gerencia quando o amarelo é aceso
void SemaCar::handle_yellow() {
// Checa se o ciclo está no intervalo (10s - 12s)
  if (millis() - start_yellow > 10000 && millis() - start_yellow < 12000)
    digitalWrite(YELLOW, HIGH);
  // Se sair desse intervalo, o amarelo desliga
  else
    digitalWrite(YELLOW, LOW); 
}

// Gerencia quando o vermelho é aceso
void SemaCar::handle_red() {
  // Checa se o ciclo está no intervalo (12s - 32s)
  if (millis() - start_red > 12000 && millis() - start_red < 32000)
    digitalWrite(RED, HIGH);
  // Se sair desse intervalo, o vermelho desliga
  else
    digitalWrite(RED, LOW);  
}

// Reseta as variáveis do ciclo
void SemaCar::restart() {
  // Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia o ciclo
  if (millis() - start_red > 32000) {
    start_green = millis();
    start_yellow = millis();
    start_red = millis();
  }
}

// Inicializar cada variável de início de cada cor
SemaCar::SemaCar() {
  start_green = millis();
  start_yellow = millis();
  start_red = millis();
}

// Método geral que executa o ciclo do semáforo dos carros
void SemaCar::work() {
  handle_green();
  handle_yellow();
  handle_red();
  restart();
}