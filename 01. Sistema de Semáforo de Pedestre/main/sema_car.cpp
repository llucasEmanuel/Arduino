#include <Arduino.h>
#include "sema_car.h"
#include "ports.h"

/* Gerencia quando o verde será aceso */
void SemaCar::handle_green() {
	// Checa se está no meio de um ciclo
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (0s - 10s)
		if (time_elapsed < 10000)
		digitalWrite(GREEN, HIGH);
		// Se sair desse intervalo, o verde desliga
		else
		digitalWrite(GREEN, LOW); 
	} 
	// Se o botão não for pressionado, o sinal fica verde para sempre
	else {
		digitalWrite(GREEN, HIGH);
	}
}

/* Gerencia quando o amarelo será aceso */
void SemaCar::handle_yellow() {
	// Checa se está no meio de um ciclo
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (10s - 12s)
		if (time_elapsed > 10000 && time_elapsed < 12000)
		digitalWrite(YELLOW, HIGH);
		// Se sair desse intervalo, o amarelo desliga
		else
		digitalWrite(YELLOW, LOW); 
	}
	// Se o botão não for pressionado, nunca fica amarelo
	else {
		digitalWrite(YELLOW, LOW);
	}
}

/* Gerencia quando o vermelho será aceso */
void SemaCar::handle_red() {
	// Checa se está no meio de um ciclo
	if (is_counting) {
		unsigned long time_elapsed = millis() - start_cycle;
		// Checa se o ciclo está no intervalo (12s - 32s)
		if (time_elapsed > 12000 && time_elapsed < 32000)
		digitalWrite(RED, HIGH);
		// Se sair desse intervalo, o vermelho desliga
		else
		digitalWrite(RED, LOW);  
	}
	// Se botão não for pressionado, nunca fica vermelho
	else {
		digitalWrite(RED, LOW);
	}
}

/* Printa a contagem regressiva para abrir o sinal dos carros no LCD */
void SemaCar::print_count(LiquidCrystal &lcd) {
	unsigned long time_elapsed = millis() - start_cycle;
	// Checa se o ciclo está no intervalo (12s - 32s)
	if (is_counting && time_elapsed > 12000 && time_elapsed < 32000) {
		// Transforma o tempo de ciclo para segundos
		int seg = time_elapsed/1000;
		// Subtrai pelo tempo total do ciclo para fazer uma contagem regressiva
		int count = 32 - seg;
		char msg[17];
		lcd.setCursor(0, 0);
		lcd.print("=TEMPO RESTANTE=");
		lcd.setCursor(0, 1);
		// Formata a mensagem da contagem regressiva para evitar sobrescrita
		sprintf(msg, "     %02d seg     ", count);
		lcd.print(msg);
	}
	// Caso contrário, o LCD é limpo
	else {
		lcd.clear();
	}
}

/* Reseta as variáveis de ciclo */
void SemaCar::restart() {
	unsigned long time_elapsed = millis() - start_cycle;
	// Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia o ciclo
	if (is_counting && time_elapsed > 32000) {
		start_cycle = millis();
		is_counting = false;
	}
}

/* Inicialização das variáveis de ciclo */
SemaCar::SemaCar() {
	start_cycle = millis();
	is_counting = false;
}

/* Checa se o botão foi apertado para atualizar as variáveis de ciclo */
void SemaCar::check_button() {
	// Se o botão for apertado (Adicionar condicial para checar se resetou o ciclo)
	if (digitalRead(BUTTON) == 0 && !is_counting) {
		start_cycle = millis();
		is_counting = true;
	}
}

/* Método geral que executa a funcionalidade do semáforo de carro */
void SemaCar::work(LiquidCrystal &lcd) {
	check_button();
	handle_green();
	handle_yellow();
	handle_red();
	print_count(lcd);
	restart();
}
