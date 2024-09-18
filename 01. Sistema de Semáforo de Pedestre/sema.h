#ifndef SEMA_H
#define SEMA_H

#include "LiquidCrystal.h"

/* Classe abstrata do semáforo */
class Semaphore {
protected:

  /* Flag que indica se o contador começou (Quando apertar o botão vai iniciar um contador de 10s para fechar o sinal de carros) */
  bool is_counting;

  /* Tempo de início de cada ciclo de cor do semáforo */
  unsigned long start_green;
  unsigned long start_red;

  /* Checa se o botaão do contador foi apertado */
  virtual void check_button() = 0;

	/* Gerencia o ciclo de cada um dos leds */
  virtual void handle_green() = 0;
  virtual void handle_red() = 0;

	/* Reinicia o ciclo */
	virtual void restart() = 0;

public:
  /* Construtor vai setar as variáveis de início de cada cor */
	Semaphore();

	/* Método geral do funcionamento do semáforo */
	virtual void work(LiquidCrystal lcd) = 0;
};

#endif
