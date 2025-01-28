#ifndef ANIMACAO_2_H
#define ANIMACAO_2_H

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "matriz-led.pio.h"

// Definições
#define NUM_PIXELS 25
#define OUT_PIN 7

// Inicializa a matriz de LEDs e executa a animação
void executar_animacao(PIO pio, uint sm);

#endif
