#include "piano.h"
#include "notes.h"
#include <Arduino.h>

Piano::Piano() {
    // Inicialização do dicionário
    notes_dict.set(C_SHARP, base_c_sharp);
    notes_dict.set(D_SHARP, base_d_sharp);
    notes_dict.set(F_SHARP, base_f_sharp);
    notes_dict.set(G_SHARP, base_g_sharp);
    notes_dict.set(A_SHARP, base_a_sharp);

    notes_dict.set(C, base_c);
    notes_dict.set(D, base_d);
    notes_dict.set(E, base_e);
    notes_dict.set(F, base_f);
    notes_dict.set(G, base_g);
    notes_dict.set(A, base_a);
    notes_dict.set(B, base_b);


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
    // Checa os botões
    if (digitalRead(C) == LOW) tone(speak_pin, octave_mult * base_c), note_played = C;
    if (digitalRead(C_SHARP) == LOW) tone(speak_pin, octave_mult * base_c_sharp), note_played = C_SHARP;
    if (digitalRead(D) == LOW) tone(speak_pin, octave_mult * base_d), note_played = D;
    if (digitalRead(D_SHARP) == LOW) tone(speak_pin, octave_mult * base_d_sharp), note_played = D_SHARP;
    if (digitalRead(E) == LOW) tone(speak_pin, octave_mult * base_e), note_played = E;
    if (digitalRead(F) == LOW) tone(speak_pin, octave_mult * base_f), note_played = F;
    if (digitalRead(F_SHARP) == LOW) tone(speak_pin, octave_mult * base_f_sharp), note_played = F_SHARP;
    if (digitalRead(G) == LOW) tone(speak_pin, octave_mult * base_g), note_played = G;
    if (digitalRead(G_SHARP) == LOW) tone(speak_pin, octave_mult * base_g_sharp), note_played = G_SHARP;
    if (digitalRead(A) == LOW) tone(speak_pin, octave_mult * base_a), note_played = A;
    if (digitalRead(A_SHARP) == LOW) tone(speak_pin, octave_mult * base_a_sharp), note_played = A_SHARP;
    if (digitalRead(B) == LOW) tone(speak_pin, octave_mult * base_b), note_played = B;

    return note_played;
}

void Piano::manage_leds() {
  
  float brightness;
  brightness = (32 * get_octave()) - 1;

  Serial.println(brightness);

  // LED verde 1
  if (digitalRead(C) == LOW || digitalRead(C_SHARP) == LOW) analogWrite(LED_C, brightness);
  else analogWrite(LED_C, 0);
  
  // LED azul 1
  if (digitalRead(D) == LOW || digitalRead(C_SHARP) == LOW || digitalRead(D_SHARP) == LOW) analogWrite(LED_D, brightness);
  else analogWrite(LED_D, 0);

  // LED vermelho 1
  if (digitalRead(E) == LOW || digitalRead(D_SHARP) == LOW) analogWrite(LED_E, brightness);
  else analogWrite(LED_E, 0);

  // LED amarelo
  if (digitalRead(F) == LOW || digitalRead(F_SHARP) == LOW) analogWrite(LED_F, brightness);
  else analogWrite(LED_F, 0);

  // LED vermelho 2
  if (digitalRead(G) == LOW || digitalRead(F_SHARP) == LOW || digitalRead(G_SHARP) == LOW) analogWrite(LED_G, brightness);
  else analogWrite(LED_G, 0);

  // LED azul 2
  if (digitalRead(A) == LOW || digitalRead(A_SHARP) == LOW || digitalRead(G_SHARP) == LOW) analogWrite(LED_A, brightness);
  else analogWrite(LED_A, 0);

  // LED verde 2
  if (digitalRead(B) == LOW || digitalRead(A_SHARP) == LOW) analogWrite(LED_B, brightness);
  else analogWrite(LED_B, 0);


}

int Piano::get_led(int note) {
  return leds_dict.get(note);
}

void Piano::turn_all_leds(bool on) {
  digitalWrite(LED_C, on);
  digitalWrite(LED_D, on);
  digitalWrite(LED_E, on);
  digitalWrite(LED_F, on);
  digitalWrite(LED_G, on);
  digitalWrite(LED_A, on);
  digitalWrite(LED_B, on);
}

void Piano::play_idle_song(int speak_pin, volatile int &state) {
  int melody[] = {
      REST,2, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8, //1
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_A4,8, NOTE_FS5,8, NOTE_E5,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 

      REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_G4,4, NOTE_B4,8, //7
      NOTE_A4,4, NOTE_B4,8, NOTE_A4,4, NOTE_D4,2,
      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_A4,8, NOTE_FS5,8, NOTE_E5,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 

      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8, //13
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_G4,4, NOTE_B4,8,
      NOTE_A4,4, NOTE_B4,8, NOTE_A4,4, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,8,
      NOTE_E4,-1,
      REST,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,-1,

      REST,8, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,8, NOTE_F4,-1, //20
      REST,8, NOTE_D4,8, NOTE_F4,8, NOTE_E4,-1, //end 1

      //repeats from 1

      REST,2, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8, //1
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_A4,8, NOTE_FS5,8, NOTE_E5,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 

      REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_G4,4, NOTE_B4,8, //7
      NOTE_A4,4, NOTE_B4,8, NOTE_A4,4, NOTE_D4,2,
      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_A4,8, NOTE_FS5,8, NOTE_E5,4, NOTE_D5,8,
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 

      REST,4, NOTE_D5,8, NOTE_B4,4, NOTE_D5,8, //13
      NOTE_CS5,4, NOTE_D5,8, NOTE_CS5,4, NOTE_A4,2, 
      REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_G4,4, NOTE_B4,8,
      NOTE_A4,4, NOTE_B4,8, NOTE_A4,4, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,8,
      NOTE_E4,-1,
      REST,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,-1,

      REST,8, NOTE_D4,8, NOTE_D4,8, NOTE_FS4,8, NOTE_F4,-1, //20
      REST,8, NOTE_D4,8, NOTE_F4,8, NOTE_E4,8, //end 2
      NOTE_E4,-2, NOTE_A4,8, NOTE_CS5,8, 
      NOTE_FS5,8, NOTE_E5,4, NOTE_D5,8, NOTE_A5,-4,
  };
  // Metrônomo
  int tempo = 140;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  int wholenote = (60000 * 4) / tempo;
  int divider = 0;
  int noteDuration = 0;
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    turn_all_leds(true);
    tone(speak_pin, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speak_pin);

    if (state == READY) {
      turn_all_leds(false);
      return;
    }
  }
}