#ifndef PIANO_H
#define PIANO_H

#include <Arduino.h>
#include <Dictionary.h>

class Piano {
private:
    // Dicionário que mapeia as portas de cada botão acionado em 0 (Cinzas) a suas notas
    Dictionary<int, float> notes_dict;
    // Dicionário que mapeia os pinos das notas aos pinos dos leds correspondentes
    Dictionary<int, int> leds_dict;
    // Multiplicador de acordo com a oitava
    int octave_mult;

    // Timeout de cada nota do idle_song
    unsigned long idle_timeout;

public:
    // Construtor da classe
    Piano();
    // Retorna o LED correspondente à nota
    int get_led(int note);
    // Retorna a oitava
    int get_octave();
    // Aumenta a oitava
    void octave_up();
    // Diminui a oitava
    void octave_down();
    // Checa e toca a nota (Se tocar alguma nota retorna true, caso contrário retorna false)
    int play_note(int speak_pin);
    // Toca uma música ambiente e curta em loop enquanto ninguém toca
    void play_idle_song(int speak_pin); // Fica 1 min esperando alguém tocar, se não toca a música em loop
    // Gerencia quando os leds acendem e apagam
    void manage_leds();
  

};

#endif // PIANO_H