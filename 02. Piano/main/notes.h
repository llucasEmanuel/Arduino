/* Portas dos botões que representam cada nota */
#define C       22  
#define C_SHARP 26
#define D       30
#define D_SHARP 34
#define E       38
#define F       42
#define F_SHARP 24
#define G       28
#define G_SHARP 32
#define A       36
#define A_SHARP 40
#define B       44


/* Portas dos LEDs que brilham conforme a oitava da nota */
#define LED_C 13
#define LED_D 12
#define LED_E 11
#define LED_F 10
#define LED_G 9
#define LED_A 8
#define LED_B 7

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
/* C - C# - D | D# - E - F 
  F# - G - G# | A - A# - B */

// Layout de Cores (Vm = Vermelho, Am = Amarelo, Vd = Verde, Az = Azul)
/* Vm - # - Am | # - Vd - Az
    # - Vd - # | Am - # - Vm  */
    