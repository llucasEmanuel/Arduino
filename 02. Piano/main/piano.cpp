#include "piano.h"
#include "notes.h"
#include <Arduino.h>

Piano::Piano() {
    // Inicialização do dicionário
    notes_dict.set(C, base_c);
    notes_dict.set(D, base_d);
    notes_dict.set(E, base_e);
    notes_dict.set(F, base_f);
    notes_dict.set(G, base_g);
    notes_dict.set(A, base_a);
    notes_dict.set(B, base_b);

    notes_dict.set(C_SHARP, base_c_sharp);
    notes_dict.set(D_SHARP, base_d_sharp);
    notes_dict.set(F_SHARP, base_f_sharp);
    notes_dict.set(G_SHARP, base_g_sharp);
    notes_dict.set(A_SHARP, base_a_sharp);

    leds_dict.set(C, LED_C);
    leds_dict.set(C_SHARP, LED_C);
    leds_dict.set(D, LED_D);
    leds_dict.set(D_SHARP, LED_D);
    leds_dict.set(E, LED_E);
    leds_dict.set(F, LED_F);
    leds_dict.set(F_SHARP, LED_F);
    leds_dict.set(G, LED_G);
    leds_dict.set(G_SHARP, LED_G);
    leds_dict.set(A, LED_A);
    leds_dict.set(A_SHARP, LED_A);
    leds_dict.set(B, LED_B);
    // Inicializa a oitava como 4
    octave_mult = 4;
}

int Piano::get_octave() {
  return octave_mult;
}

void Piano::octave_up() {
  octave_mult++;
  if (octave_mult > 8) octave_mult = 8;
}

void Piano::octave_down() {
  octave_mult--;
  if (octave_mult <= 0) octave_mult = 1;
}

int Piano::play_note(int speak_pin) {
    int note_played = -1;
    // Checa os botões coloridos
    for (int i = 0; i < notes_dict.length(); i++) {
        // Se a nota for tocada
        int note = notes_dict.getKeyByIndex(i);
        if(digitalRead(note) == LOW) {
            tone(speak_pin, octave_mult * notes_dict.get(note));
            note_played = note;
        }
    } 
    return note_played;
}

// Encontrar uma forma de interromper a música quando alguém começar a tocar -> USAR attachInterrupt() para interromper a musica sem precisar checar toda hora
void Piano::play_idle_song(int speak_pin) {
  // Flag que faz o octave_mult ir pra baixo quando chega no máximo
  bool go_back = false;
  // Valor somado ao octave_mult
  int plus = 0;
  while(true) {

    Serial.println(plus);

    if (go_back) plus--;
    else plus++; 

    tone(speak_pin, (octave_mult + plus) * base_a);
    delay(800);
    noTone(speak_pin);

    if (octave_mult + plus > 8) go_back = true;
    if (octave_mult + plus < 4) go_back = false;
  }
}

void Piano::turn_all_leds(bool on) {
  float freq;
  if (on) freq = (32 * get_octave()) - 1;
  else freq = 0;
  digitalWrite(LED_C, freq);
  digitalWrite(LED_D, freq);
  digitalWrite(LED_E, freq);
  digitalWrite(LED_F, freq);
  digitalWrite(LED_G, freq);
  digitalWrite(LED_A, freq);
  digitalWrite(LED_B, freq);
}

int Piano::get_led(int note) {
  return leds_dict.get(note);
}
