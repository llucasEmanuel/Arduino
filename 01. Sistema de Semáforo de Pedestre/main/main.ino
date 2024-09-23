#include  <LiquidCrystal.h>
#include "sema_car.h"
#include "sema_ped.h"
#include "ports.h"

/* Instanciação global do objeto do LCD */
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

/* Instanciação global do objeto de cada semáforo */
SemaCar sema_car;
SemaPed sema_ped;

/* Inicialização das variáveis */
void setup() {
	// Mapemento das portas do semáforo de carro
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);

	// Mapeamento das portas do semáforo de pedestres
	pinMode(PED_BLUE, OUTPUT);
	pinMode(PED_RED, OUTPUT);
	pinMode(PED_GREEN, OUTPUT);
	pinMode(BUZZ, OUTPUT);

	// Mapeamento da porta do botão
	pinMode(BUTTON, INPUT_PULLUP);

	// Inicialização do terminal (DEBUG)
	Serial.begin(9600);

	// Inicialização do display LCD
	lcd.begin(16, 2);
}

/* Execução do sistema */
void loop() {
	// Execução independente de cada semáforo
	sema_car.work(lcd);
  	sema_ped.work(lcd);
}
