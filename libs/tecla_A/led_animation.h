#ifndef LED_ANIMATION_H
#define LED_ANIMATION_H

#include <stdbool.h>
#include "hardware/pio.h"
#include "teclado_matricial.h"  // Incluindo a biblioteca do teclado (ajuste conforme necessário)

// Definições dos desenhos com animações (matrizes 5x5 com valores 0.0 para os LEDs apagados)
extern double desenho1_A[25];
extern double desenho2_A[25];
extern double desenho3_A[25];
extern double desenho4_A[25];
extern double desenho5_A[25];
extern double desenho6_A[25];
extern double desenho7_A[25];
extern double desenho8_A[25];

// Função para acionar os LEDs
void led_matrix_draw_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

// Função para definir a cor do LED
uint32_t led_matrix_rgb(double b, double r, double g);

// Função principal que executa a animação
void led_matrix_main_animation(char tecla, PIO pio, uint sm);

#endif // LED_ANIMATION_H
