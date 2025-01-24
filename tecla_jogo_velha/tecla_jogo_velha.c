#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Define constante com o número de leds da matriz
#define NUM_LEDS 25

// Inicializa vetor bidimencional com animações
double animacoes[5][NUM_LEDS] = {
    {0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0, 
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0},

    {0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0, 
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0},

    {0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0, 
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0},

    {0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0, 
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0},

    {0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0, 
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0}
};

// Inicializa vetor para apagar acender todos os leds com nível de intensidade de 20% da luminosidade máxima
double animacao_20[NUM_LEDS] = {0.2, 0.2, 0.2, 0.2, 0.2,
                                0.2, 0.2, 0.2, 0.2, 0.2, 
                                0.2, 0.2, 0.2, 0.2, 0.2,
                                0.2, 0.2, 0.2, 0.2, 0.2,
                                0.2, 0.2, 0.2, 0.2, 0.2};

// Função que define a intensidade de cada cor de cada led
uint32_t matrix_rgb2(double r, double g, double b) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para acionar a matrix de leds
void animacao_pio(double *animacao, uint32_t iRgb_led, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_LEDS; i++) {
        if (i%2 == 0) {
            iRgb_led = matrix_rgb2(r = 0.0, g = 0.0, animacao[24-i]);
        }
        else {
            iRgb_led = matrix_rgb2(animacao[16-i], g = 0.0, b = 0.0);
        }
        pio_sm_put_blocking(pio, sm, iRgb_led);
    }
}

//função principal
void gera_animacao(char tecla, PIO pio, uint sm) {
    uint32_t iRgb_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    if (tecla == '#') {
        animacao_pio(animacao_20, iRgb_led, pio, sm, r, g, b);
    }
    else if (tecla == '5') {
        for (int16_t i = 0; i < 5; i++) {
            animacao_pio(animacoes[i], iRgb_led, pio, sm, r, g, b);
            sleep_ms(500);
        }
    }
    
}