#ifndef SEMA_PED_H
#define SEMA_PED_H

// Classe que representa o semáforo dos pedestres
class PedSemaphore {
private:
  // Tempo de início de cada ciclo de cor do semáforo
  unsigned long start_green;
  unsigned long start_red;

	// Variáveis auxiliares do azul
  unsigned long start_blue;
  unsigned long period_blue;
  bool is_high_blue;

  // Variáveis auxiliares do buzzer
  unsigned long start_buzz;
  unsigned long period_buzz;
  bool is_high_buzz;

	// Gerencia o ciclo geral dos leds
  void handle_red();
  void handle_green();

	// Gerencia os últimos 10s do ciclos
  void blink_blue();
  void handle_blue();
  void blink_buzz();
  void handle_buzz();

  // Reinicia o ciclo
  void restart();
public: 
  // Construtor vai setar as variáveis de início de cada cor
  PedSemaphore();

  // Método geral do funcionamento do semáforo
  void work();
};

#endif