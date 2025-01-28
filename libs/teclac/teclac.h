#ifndef ANIMACAO_C_H
#define ANIMACAO_C_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

typedef struct {
    double red;
    double green;
    double blue;
} RGB_defs;

typedef RGB_defs RGB_cod;
typedef RGB_defs Matriz_leds_config[5][5];

void imprime_desenho_c(Matriz_leds_config configuracao, PIO pio, uint sm);

void rodar_todos_frames_c(PIO pio, uint sm);

#endif