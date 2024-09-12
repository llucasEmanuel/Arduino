#include  <LiquidCrystal.h>

// Portas dos leds do sinal do transito
#define RED A5
#define YELLOW A4
#define GREEN A3

// Portas dos leds do sinal de pedestre
#define PED_BLUE A2
#define PED_RED A1
#define PED_GREEN A0

// Portas do display LCD 
#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Porta do botão 
#define BUTTON 12

// Porta do buzzer 
#define BUZZ 13

// Instanciação do objeto do LCD
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

// Classe que representa o semáforo dos carros
class Semaphore {
private:
  // Tempo de início de cada ciclo de cor do semáforo
  unsigned long start_green;
  unsigned long start_yellow;
  unsigned long start_red;

  // Gerencia quando o verde será aceso
  void handle_green() {
    // Checa se o ciclo está no intervalo (0s - 10s)
    if (millis() - start_green < 10000)
      digitalWrite(GREEN, HIGH);
    // Se sair desse intervalo, o verde desliga
    else
      digitalWrite(GREEN, LOW);  
  }

  // Gerencia quando o amarelo será aceso
  void handle_yellow() {
    // Checa se o ciclo está no intervalo (10s - 12s)
    if (millis() - start_yellow > 10000 && millis() - start_yellow < 12000)
      digitalWrite(YELLOW, HIGH);
    // Se sair desse intervalo, o amarelo desliga
    else
      digitalWrite(YELLOW, LOW);  
  }

  // Gerencia quando o vermelho será aceso
  void handle_red() {
    // Checa se o ciclo está no intervalo (12s - 32s)
    if (millis() - start_red > 12000 && millis() - start_red < 32000)
      digitalWrite(RED, HIGH);
    // Se sair desse intervalo, o vermelho desliga
    else
      digitalWrite(RED, LOW);  
  }

  // Reseta as variáveis do ciclo
  void restart() {
    // Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia ele
    if (millis() - start_red > 32000) {
      start_green = millis();
      start_yellow = millis();
      start_red = millis();
    }
  }
public:
  // Inicializar cada variável de início de cada cor
  Semaphore() {
    start_green = millis();
    start_yellow = millis();
    start_red = millis();
  }

  // Método geral que executa o ciclo do semáforo dos carros
  void work() {
    handle_green();
    handle_yellow();
    handle_red();
    restart();
  }
};

// Classe que representa o semáforo dos pedestres
class PedSemaphore {
private:
  // Tempo de início de cada ciclo de cor do semáforo
  unsigned long start_green;
  unsigned long start_red;

  // Variáveis auxiliares do led azul
  unsigned long start_blue;
  unsigned long period_blue;
  bool is_high_blue;

  // Variáveis auxiliares do buzzer
  unsigned long start_buzz;
  unsigned long period_buzz;
  bool is_high_buzz;

  // Gerencia quando o vermelho será aceso
  void handle_red() {
    // Checa se o ciclo está no intervalo (0s - 12s)
    if (millis() - start_red < 12000) 
      digitalWrite(PED_RED, HIGH);
    // Se sair desse intervalo, o vermelho desliga
    else
      digitalWrite(PED_RED, LOW);  
  }

  // Gerencia quando o vermelho será aceso
  void handle_green() {
    // Checa se o ciclo está no intervalo (12s - 32s)
    if (millis() - start_green > 12000 && millis() - start_green < 32000)
      digitalWrite(PED_GREEN, HIGH);
    // Se sair desse intervalo, o verde desliga
    else
      digitalWrite(PED_GREEN, LOW);  
  }

  // Faz o led azul piscar numa frequência de 2Hz
  void blink_blue() {
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

  // Gerencia quando o azul será aceso
  void handle_blue() {
    // Checa se o ciclo está no intervalo (22s - 32s) -> Últimos 10s do led vermelho do pedestre
    if (millis() - start_blue > 22000 && millis() - start_blue < 32000)
      blink_blue();
    // Se sair desse intervalo, o azul desliga
    else
      digitalWrite(PED_BLUE, LOW);
  }

  // Faz o buzzer apitar numa frequência de 1Hz 
  void blink_buzz() {
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

  // Gerencia quando o buzzer apita
  void handle_buzz() {
    // Checa se o ciclo está no intervalo (22s - 32s) -> Últimos 10s do led vermelho do pedestre
    if (millis() - start_blue > 22000 && millis() - start_blue < 32000)
      blink_buzz();
    // Se sair desse intervalo, o azul desliga
    else
      noTone(BUZZ);
  }

  // Reseta as variáveis do ciclo
  void restart() {
    // Se o tempo total do ciclo (32s) tiver sido ultrapassado, reinicia ele
    if (millis() - start_green > 32000) {
      start_green = millis();
      start_red = millis();
      start_blue = millis();
      period_blue = millis();
      period_buzz = millis();
    }
  }

public: 
  // Inicializar cada variável de início de cada cor
  PedSemaphore() {
    start_green = millis();
    start_red = millis();
    start_blue = millis();
    period_blue = millis();
    period_buzz = millis();
  }

  // Método geral que executa o ciclo do semáforo dos pedestres
  void work() {
    handle_green();
    handle_red();
    handle_blue();
    handle_buzz();
    restart();
  }
};

// Instanciação global dos objetos semaforos
Semaphore sem_car;
PedSemaphore sem_ped;

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
  sem_car.work();
  sem_ped.work();
}
