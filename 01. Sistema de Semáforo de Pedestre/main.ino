#include  <LiquidCrystal.h>
#include "sema_car.h"
#include "sema_ped.h"
#include "ports.h"

// Instanciação do objeto do LCD
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

// Instanciação global dos objetos semaforos
SemaCar sema_car;
SemaPed sema_ped;

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

  // Inicialização do terminal e do display LCD
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // Execução do sistema de semáforos
  sema_car.work(lcd);
  sema_ped.work(lcd);
}
