#include "piano.h"
#include "notes.h"

/* Porta do speaker */
#define SPEAKER 42

/* Portas dos botões de mudança de oitava */
#define BTN_DOWN 13
#define BTN_UP 22

/* Pora do botão que troca o estado de IDLE para READY */
#define BTN_STATE 20

/* Tempo em millisegundos da duração do bounce */
#define BOUNCE_TIME 30

/* Flags dos botões de frequência */
bool pressed_up = false;
bool pressed_down = false;

/* Variáveis auxiliares dos botões de nota */
bool playing = false; // Flag que indica se alguma nota está sendo tocada
int note_played = -1;
unsigned long stadby_time;
unsigned long play_timeout; // Indica quando a última nota foi tocada

/* Estado do piano */
// O estado será trocado para IDLE após passar um determinado tempo sem o usuário tocar
volatile int state;
volatile unsigned long bounce_start = 0;
void change_state() {
  if (millis() > bounce_start) {
    state = !state;
    bounce_start = millis() + BOUNCE_TIME;
  }
}

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

  // Mapeamento do botão de mudança de frequência
  pinMode(BTN_STATE, INPUT_PULLUP);

  // BTN_STATE vai mudar (ou manter) o estado para READY quando apertado
  attachInterrupt(digitalPinToInterrupt(BTN_STATE), change_state, RISING);

  // Mapeamento do LED
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Inicialização do terminal (DEBUG)
  Serial.begin(9600);

  // Estado do piano inicialmente setado para ser IDLE
  state = IDLE;
}

/* Execução do sistema */
void loop() {

  while (state == IDLE) {
    Serial.println("Playing idle song");
    piano.play_idle_song(SPEAKER, state);
  }

  Serial.println(state);

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
    
    note_played = piano.play_note(SPEAKER);
    if (note_played != -1) {
      playing = true;
      // Printa a porta do botão pressionado
      Serial.println(note_played);
    }
    else playing = false;

    // Se estiver tocando
    if (playing) {
      // Printa no terminal a oitava atual
      char msg[51];
      sprintf(msg, "octave = %d", piano.get_octave());
      Serial.println(msg);
      // Reseta o timeout de tocar a nota (inicia a contagem de 200 ms)
      play_timeout = millis();
    }
  }
  // Se estiver tocando
  else {
    // Checa se passou o timeout de 200ms
    if (millis() - play_timeout > 200) {
      // Pode tocar novamente e reseta o timeout
      noTone(SPEAKER);
      playing = false;
      play_timeout = millis();
    }
  }
  piano.manage_leds(); 

}

