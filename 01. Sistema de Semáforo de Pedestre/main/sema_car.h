#ifndef SEMA_CAR_H
#define SEMA_CAR_H

#include "sema.h"
#include "LiquidCrystal.h"

/* Classe que representa o semáforo dos carros */
class SemaCar : public Semaphore {
private:
	// Gerencia o ciclo do led amarelo
	void handle_yellow();

	// Printa a contagem regressiva no LCD
	void print_count(LiquidCrystal &lcd);
	
	// Gerencia o ciclo de cada um dos leds
	void handle_green() override;
	void handle_red() override;

	// Checa se o botão foi apertado
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
