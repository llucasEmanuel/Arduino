#ifndef SEMA_PED_H
#define SEMA_PED_H

#include "sema.h"
#include "LiquidCrystal.h"

/* Classe que representa o semáforo dos pedestres */
class SemaPed : public Semaphore {
private:
	// Variáveis auxiliares do azul
	unsigned long period_blue;
	bool is_high_blue;

	// Variáveis auxiliares do buzzer
	unsigned long period_buzz;
	bool is_high_buzz;

	// Gerencia o azul e o buzzer
	void blink_blue();
	void handle_blue();
	void blink_buzz();
	void handle_buzz();

	// Checa se o botão foi apertado
	void check_button() override;

	// Gerencia o ciclo geral dos leds
	void handle_red() override;
	void handle_green() override;

	// Reinicia o ciclo
	void restart() override;
public: 
	// Construtor vai setar as variáveis de início de cada cor
	SemaPed();

	// Método geral do funcionamento do semáforo
	void work(LiquidCrystal &lcd) override;
};

#endif
