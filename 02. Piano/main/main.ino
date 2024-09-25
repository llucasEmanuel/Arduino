#define A       12
#define A_SHARP 10 
#define B       8
#define C       6  
#define C_SHARP 4
#define D       2
#define D_SHARP 11
#define E       9
#define F       7
#define F_SHARP 5
#define G       3
#define G_SHARP 22

#define SPEAKER 13

void setup() {
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

  pinMode(SPEAKER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(A) == 0) tone(SPEAKER, 440, 250);
}

