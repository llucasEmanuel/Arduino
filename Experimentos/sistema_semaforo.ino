#define RED 11
#define YELLOW 12
#define GREEN 13

#define PED_GREEN 2
#define PED_RED 3

#define BLUE 5
#define BUZZER 7

void acenderVerde();
void acenderAmarelo();
void acenderVermelho();

void setup() {
  // mapeamento dos pinos de cada led
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(PED_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);

  pinMode(BLUE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  acenderVermelho(10000);
  acenderVerde(7000);
  acenderAmarelo(2000);
}

void acenderVerde(int time_delay) {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  
  digitalWrite(PED_GREEN, LOW);
  digitalWrite(PED_RED, HIGH);

  delay(time_delay);
}
void acenderAmarelo(int time_delay) {
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);

  delay(time_delay);
}
void acenderVermelho(int time_delay) {
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);

  digitalWrite(PED_RED, LOW);
  digitalWrite(PED_GREEN, HIGH);

  delay(time_delay/2);

  for (int i = 0; i < 5; i++) {
    digitalWrite(BLUE, HIGH);
    tone(BUZZER, 440);
    delay(500);
    noTone(BUZZER);
    digitalWrite(BLUE, LOW);
    delay(500);
  }
}
