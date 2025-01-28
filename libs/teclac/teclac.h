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

void animate_red_pulse(PIO pio, uint sm);
void setup_animation(PIO pio, uint sm);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "animação_c.h"

// Definindo a cor vermelha
static const RGB_cod cor_vermelha = {1.0, 0.0, 0.0}; // Vermelho
static const RGB_cod cor0 = {0.0, 0.0, 0.0}; // Preto

Matriz_leds_config frame0 = {
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame1 = {
    {cor_ver
