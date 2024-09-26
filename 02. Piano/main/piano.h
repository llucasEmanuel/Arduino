#ifndef PIANO_H
#define PIANO_H

#include <Arduino.h>
#include <Dictionary.h>

class Piano {
private:
    // Dicionário que mapeia as portas de cada nota à sua frequência
    Dictionary<int, float> notes_dict;
    // Multiplicador de acordo com a oitava
    int octave_mult;

    // Timeout de cada nota do idle_song
    unsigned long idle_timeout;

public:
    // Construtor da classe
    Piano();
    // Retorna a oitava
    int get_octave();
    // Aumenta a oitava
    void octave_up();
    // Diminui a oitava
    void octave_down();
    // Checa e toca a nota (Se tocar alguma nota retorna true, caso contrário retorna false)
    bool play_note(int speak_pin);
    // Toca uma música ambiente e curta em loop enquanto ninguém toca
    void play_idle_song(int speak_pin); // Fica 1 min esperando alguém tocar, se não toca a música em loop
  

};

#endif // PIANO_H