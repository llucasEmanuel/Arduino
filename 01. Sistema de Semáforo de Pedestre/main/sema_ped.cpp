#include <Arduino.h>
#include "sema_ped.h"
#include "ports.h"

/* Gerencia quando o vermelho será acesso */
void SemaPed::handle_red() {
	// Checa se iniciou o ciclo
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (0s - 12s)
		if (time_elapsed < 12000) 
		digitalWrite(PED_RED, HIGH);
		// Se sair desse intervalo, o vermelho desliga
		else
		digitalWrite(PED_RED, LOW);    
	}
	// Se o botão não for pressionado, o sinal fica vermelho para sempre
	else {
		digitalWrite(PED_RED, HIGH);
	}
}

/* Gerencia quando o verde será acesso */
void SemaPed::handle_green() {
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (12s - 32s)
		if (time_elapsed > 12000 && time_elapsed < 32000)
		digitalWrite(PED_GREEN, HIGH);
		// Se sair desse intervalo, o verde desliga
		else
		digitalWrite(PED_GREEN, LOW);  
	}
	// Se o botão não for pressionado, o sinal nunca fica verde
	else {
		digitalWrite(PED_GREEN, LOW);
	}
}

/* Faz o azul piscar numa frequência de 2Hz */
void SemaPed::blink_blue() {
	// Checa se o período chegou ao fim (T = 0.5s)
	if (millis() - period_blue > 500) {
		// Se o azul estiver desligado, ele é ligado e a flag é ativada
		if (!is_high_blue) {
			digitalWrite(PED_BLUE, HIGH);
			is_high_blue = true;
		}
		// Caso contrário, ele é desligado e a flag é desativada
		else {
			digitalWrite(PED_BLUE, LOW);
			is_high_blue = false;
		}
		// A cada 0.5s a variável de início do período é recalculada
		period_blue = millis();
	}
}

/* Gerencia quando o azul será acesso */
void SemaPed::handle_blue() {
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (22s - 32s) -> Últimos 10s do led vermelho do pedestre
		if (time_elapsed > 22000 && time_elapsed < 32000)
			blink_blue();
		// Se sair desse intervalo, o azul desliga
		else
			digitalWrite(PED_BLUE, LOW);
	}
	else {
		digitalWrite(PED_BLUE, LOW);
	}
}

/* Faz o buzzer apitar numa frequência de 1Hz */
void SemaPed::blink_buzz() {
	// Checa se o período chegou ao fim (T = 1s)
	if (millis() - period_buzz > 1000) {
		// Se o buzzer não estiver apitando, ele apita e a flag é ativada
		if (!is_high_buzz) {
			tone(BUZZ, 440);
			is_high_buzz = true;
		}
		// Caso contrário, ele para de apitar e a flag é desativada
		else {
			noTone(BUZZ);
			is_high_buzz = false;
		}
		// A cada 1s a variável de início do período é recalculada
		period_buzz = millis();
	}
}

/* Gerencia quando o buzzer apita */
void SemaPed::handle_buzz() {
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (22s - 32s) -> Últimos 10s do led vermelho do pedestre
		if (time_elapsed > 22000 && time_elapsed < 32000)
			blink_buzz();
		// Se sair desse intervalo, o azul desliga
		else
			noTone(BUZZ);
	}
	else {
		noTone(BUZZ);
	}
}

/* Reseta as variáveis de ciclo */
void SemaPed::restart() {
	unsigned long time_elapsed = millis() - start_cycle;
	// Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia ele
	if (is_counting && time_elapsed > 32000) {
		start_cycle = millis();
		period_blue = millis();
		period_buzz = millis();
		is_counting = false;
	}
}

// Inicializar cada variável de início de cada cor
SemaPed::SemaPed() {
	start_cycle = millis();
	period_blue = millis();
	period_buzz = millis();
	is_counting = false;
}

void SemaPed::check_button() {
	// Se o botão for apertado (Adicionar condicial para checar se resetou o ciclo)
	if (digitalRead(BUTTON) == 0 && !is_counting) {
		start_cycle = millis();
		is_counting = true;
	}
}

// Método geral que executa o ciclo do semáforo dos pedestres
void SemaPed::work(LiquidCrystal &lcd) {
	check_button();
	handle_green();
	handle_red();
	handle_blue();
	handle_buzz();
	restart();
}
