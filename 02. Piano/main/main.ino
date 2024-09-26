#include "piano.h"
#include "notes.h"

/* Porta do speaker */
#define SPEAKER 50

/* Portas dos botões de mudança de oitava */
#define BTN_DOWN 48
#define BTN_UP 52

/* Porta do LED que brilha conforme a oitava da nota */
#define LED 8

/* Flags dos botões de frequência */
bool pressed_up = false;
bool pressed_down = false;

/* Variáveis auxiliares dos botões de nota */
bool playing = false; // Flag que indica se alguma nota está sendo tocada
unsigned long stadby_time;
unsigned long play_timeout; // Indica quando a última nota foi tocada

/* Instanciação global do objeto piano */
Piano piano;

/* Inicialização das variáveis */
void setup() {
  // Mapemento dos botões de cada nota
  pinMode(A, INPUT_PULLUP);
  pinMode(A_SHARP, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(C_SHARP, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(D_SHARP, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(F_SHARP, INPUT_PULLUP);
  pinMode(G, INPUT_PULLUP);
  pinMode(G_SHARP, INPUT_PULLUP);

  // Mapeamento do speaker
  pinMode(SPEAKER, OUTPUT);

  // Mapeamento dos botões de mudança de frequência
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  // Mapeamento do LED
  pinMode(LED, OUTPUT);

  // Inicialização do terminal (DEBUG)
  Serial.begin(9600);
}

/* Execução do sistema */
void loop() {

  //piano.play_idle_song(SPEAKER);

  // Checa se o botão de oitava acima foi pressionado
  if (digitalRead(BTN_UP) == 0 && !pressed_up) {
    pressed_up = true;
    piano.octave_up();
  }
  // Caso contrário, seta a flag para falso para evitar incrementar ao segurar
  else if (digitalRead(BTN_UP) == 1) {
    pressed_up = false;
  } 

  // Checa se o botão de oitava abaixo foi pressionado
  if (digitalRead(BTN_DOWN) == 0 && !pressed_down) {
    pressed_down = true;
    piano.octave_down();
  }
  // Caso contrário, seta a flag para falso para evitar incrementar ao segurar
  else if (digitalRead(BTN_DOWN) == 1) {
    pressed_down = false;
  } 

  // Se não estiver tocando
  if (!playing) {
    
    playing = piano.play_note(SPEAKER);

    // Se estiver tocando
    if (playing) {
      // Printa no terminal a oitava atual
      char msg[51];
      sprintf(msg, "octave = %d", piano.get_octave());
      Serial.println(msg);
      // Acende o LED de acordo com a oitava atual
      analogWrite(LED, 32 * piano.get_octave() - 1);
      // Reseta o timeout de tocar a nota (inicia a contagem de 200 ms)
      play_timeout = millis();
    }
    else {
      // Se não estiver tocando, desliga o LED
      analogWrite(LED, 0);
    }
  }
  // Se estiver tocando
  else {
    // Checa se passou o timeout de 200ms
    if (millis() - play_timeout > 200) {
      // Pode tocar novamente e reseta o timeout
      analogWrite(LED, 0);
      noTone(SPEAKER);
      playing = false;
      play_timeout = millis();
    }
  }
}
