#include "piano.h"
#include "notes.h"
#include <Arduino.h>

Piano::Piano() {
    // Inicialização do dicionário
    notes_dict.set(C, base_c);
    notes_dict.set(C_SHARP, base_c_sharp);
    notes_dict.set(D, base_c);
    notes_dict.set(D_SHARP, base_d);
    notes_dict.set(E, base_e);
    notes_dict.set(F, base_f);
    notes_dict.set(F_SHARP, base_f_sharp);
    notes_dict.set(G, base_g);
    notes_dict.set(G_SHARP, base_g_sharp);
    notes_dict.set(A, base_a);
    notes_dict.set(A_SHARP, base_a_sharp);
    notes_dict.set(B, base_b);
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

bool Piano::play_note(int speak_pin) {
    bool note_played = false;
    for (int i = 0; i < notes_dict.length(); i++) {
        // Se a nota for tocada
        int note = notes_dict.getKeyByIndex(i);
        if(digitalRead(note) == 0) {
            tone(speak_pin, octave_mult * notes_dict.get(note));
            note_played = true;
        }
    } 
    return note_played;
}

// Encontrar uma forma de interromper a música quando alguém começar a tocar
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