#ifndef SEMA_CAR_H
#define SEMA_CAR_H

#include "sema.h"

// Classe que representa o semáforo dos carros
class SemaCar : public Semaphore {
private:
  // Gerencia o ciclo de cada um dos leds
  void handle_green() override;
  void handle_yellow() override;
  void handle_red() override;

  // Reinicia o ciclo
  void restart() override;
public:
  // Construtor vai setar as variáveis de início de cada cor
  SemaCar();
  
  // Método geral do funcionamento do semáforo
  void work() override;
};

#endif