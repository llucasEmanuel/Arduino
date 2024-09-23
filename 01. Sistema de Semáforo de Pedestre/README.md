# Sistema de Semáforo de Pedestre

## Introdução
Esse projeto consiste em uma simulação de um sistema de semáforos real usando *Arduino*. Ele possui a funcionalidade de um semáforo para os carros, um semáforo para os pedestres e um botão apertado pelos pedestres para fechar o sinal dos carros.

## Componentes
- 1 Arduino UNO
- 1 Protoboard
- 1 Display LCD 16x2
- 1 Buzzer
- 1 Botão de 2 pinos
- 1 Potenciômetro de 10k Ohms
- 1 LED amarelo
- 1 LED azul
- 2 LEDs verdes
- 2 LEDs vermelhos
- 6 Resistores de 330 Ohms
  
## Funcionamento
### Estado Padrão
O estado inicial do sistema consiste no semáforo dos carros aberto (LED verde dos carros aceso) e o semáforo dos pedestres fechado (LED vermelho dos pedestres aceso). Pois, foi usada a lógica de que o semáforo dos carros só fecha se houver pedestres, ou seja, se o botão for apertado.
O sistema fica nesse ciclo até o botão ser pressionado.
### Ciclo: Primeira Parte
Quando o botão é pressionado é iniciada um contagem de 10 segundos, em que ao fim dela o LED verde dos carros será apagado.
Isso ocorre durante o intervalo (0s - 10s) do ciclo.
### Ciclo: Segunda Parte
Quando o LED verde dos carros é apagado, o LED amarelo é aceso e mantém seu estado durante 2 segundos. No entanto, o semáforo dos pedestres permanece inalterado, já que o semáforo dos carros ainda não fechou completamente.
Isso ocorre durante o intervalo (10s - 12s) do ciclo.
### Ciclo: Terceira Parte
Quando o LED amarelo é apagado, o LED vermelho dos carros é aceso e o LED verde dos pedestres é aceso ao mesmo tempo que o LED vermelho dos pedestres é apagado. Com isso, os pedestres estariam livres para atravessar. O sinal fica vermelho por 20 segundos ao todo, mas nos 10 segundos finais o estado muda. Além disso, é printado no display LCD o tempo restante para abrir o semáforo dos carros.
Isso ocorre durante o intervalo (12s - 22s) do ciclo.
### Ciclo: Quarta Parte
Quando o ciclo chega nos seus 10 segundos finais, o LED azul começa a piscar numa frequência de 2 Hz e o buzzer começa a apitar numa frequência de 1 Hz, tudo isso como uma forma de avisar ao pedestre que o semáforo dos carros está próximo de abrir. Quando o ciclo chega em 32 segundos o semáforo dos carros abre, o led azul e o buzzer param, e o sistema volta para o **Estado Padrão**.
Isso ocorre durante o intervalo (22s - 32s) do ciclo.
  
