#ifndef SEMA_CAR_H
#define SEMA_CAR_H

#include "sema.h"
#include "LiquidCrystal.h"

// Classe que representa o semáforo dos carros
class SemaCar : public Semaphore {
private:
  /* Tempo de início do ciclo amarelo */
  unsigned long start_yellow;

  // Gerencia o ciclo do led amarelo
  void handle_yellow();

  void print_count(LiquidCrystal &lcd);
  
  // Gerencia o ciclo de cada um dos leds
  void handle_green() override;
  void handle_red() override;

  void check_button() override;

  // Reinicia o ciclo
  void restart() override;
public:
  // Construtor vai setar as variáveis de início de cada cor
  SemaCar();
  
  // Método geral do funcionamento do semáforo
  void work(LiquidCrystal &lcd) override;
};

#endif
