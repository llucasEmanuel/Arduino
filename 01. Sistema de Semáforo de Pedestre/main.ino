#include  <LiquidCrystal.h>

// Portas dos leds do sinal do transito (Analógico)
#define RED A5
#define YELLOW A4
#define GREEN A3

// Portas dos leds do sinal de pedestre (Analógico)
#define PED_BLUE A2
#define PED_RED A1
#define PED_GREEN A0

#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Porta do botão (Digital)
#define BUTTON 12

// Relacionados ao tempo
unsigned long millisCarro = millis();
unsigned long millisPedestre = millis();
unsigned long forBlue = millis();
unsigned long forBuzzer = millis();

// false -> botão não foi apertado | true -> botão foi apertado
bool flagAperta = false;
// true -> pode entrar em um novo ciclo | false -> não pode entrar em um novo ciclo
bool flagPosso = true;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  // Mapemento dos LEDS
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PED_BLUE, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  // Mapeamento do botão
  pinMode(BUTTON, INPUT_PULLUP);
  // Inicialização monitor e lcd
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("AAAAAAAAAAAAAAAA");
}

void loop() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(PED_BLUE, HIGH);
  digitalWrite(PED_RED, HIGH);
  digitalWrite(PED_GREEN, HIGH);

  Serial.println(digitalRead(BUTTON));
  //sinal_carro();
  //sinal_pedestre();
}

void sinal_carro() {
  if(digitalRead(BUTTON) == LOW) {
    flagAperta = true;
  }
  
}

void sinal_pedestre() {

}


