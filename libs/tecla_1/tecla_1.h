#ifndef TECLA_1_H
#define TECLA_1_H

// Criando estrutura struct para controlar a cor dos LEDS
typedef struct {
    double red;
    double green;
    double blue;
}RGB_defs;

typedef RGB_defs RGB_cod;
typedef RGB_defs Matriz_leds_config[5][5]; 

uint32_t gera_binario_rgb(double red, double green, double blue);

void imprime_desenho(Matriz_leds_config configuracao, PIO pio, uint sm);

void desenho_tecla1(PIO pio, uint sm);


#endif