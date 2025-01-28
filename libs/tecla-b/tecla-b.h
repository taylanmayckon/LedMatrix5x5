#ifndef TECLA_B_H
#define TECLA_B_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

// Função para ligar os LEDs verdes ao pressionar a tecla 'B'
void ligar_leds_verdes(PIO pio, uint sm);

#endif
