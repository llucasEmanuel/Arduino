#ifndef SEMA_H
#define SEMA_H

/* Classe abstrata do semáforo */
class Semaphore {
protected:
  /* Tempo de início de cada ciclo de cor do semáforo */
  unsigned long start_green;
  unsigned long start_yellow;
  unsigned long start_red;

	/* Gerencia o ciclo de cada um dos leds */
  virtual void handle_green() = 0;
  virtual void handle_yellow() = 0;
  virtual void handle_red() = 0;

	/* Reinicia o ciclo */
	virtual void restart() = 0;

public:
  /* Construtor vai setar as variáveis de início de cada cor */
	Semaphore();

	/* Método geral do funcionamento do semáforo */
	virtual void work() = 0;
};

#endif