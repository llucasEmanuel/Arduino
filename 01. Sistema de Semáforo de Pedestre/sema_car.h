#ifndef SEMA_CAR_H
#define SEMA_CAR_H

// Classe que representa o semáforo dos carros
class Semaphore {
private:
  // Tempo de início de cada ciclo de cor do semáforo
  unsigned long start_green;
  unsigned long start_yellow;
  unsigned long start_red;

  // Gerencia o ciclo de cada um dos leds
  void handle_green();
  void handle_yellow();
  void handle_red();

  // Reinicia o ciclo
  void restart();
public:
  // Construtor vai setar as variáveis de início de cada cor
  Semaphore();
  
  // Método geral do funcionamento do semáforo
  void work();
};

#endif