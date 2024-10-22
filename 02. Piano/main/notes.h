/* Portas dos botões que representam cada nota */
#define C       51  
#define C_SHARP 50
#define D       49
#define D_SHARP 48
#define E       47
#define F       37
#define F_SHARP 36
#define G       35
#define G_SHARP 34
#define A       33
#define A_SHARP 32
#define B       31


/* Portas dos LEDs que brilham conforme a oitava da nota */
#define LED_C 11
#define LED_D 10
#define LED_E 9
#define LED_F 7
#define LED_G 4
#define LED_A 3
#define LED_B 2

/* Frequência da primeira oitava de cada nota */
const float base_c = 32.70;
const float base_c_sharp = 34.65;
const float base_d = 36.71;
const float base_d_sharp = 38.89;
const float base_e = 41.20;
const float base_f = 43.65;
const float base_f_sharp = 46.25;
const float base_g = 49.00;
const float base_g_sharp = 51.91;
const float base_a = 55;
const float base_a_sharp = 58.27;
const float base_b = 61.74;

// Layout dos botões
/* C   D   E   F   G   A   B
     C#  D#      F#  G#  A#  */
    