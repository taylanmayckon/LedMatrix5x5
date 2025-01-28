#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "teclac.h"

static const RGB_cod cor_vermelha = {1.0, 0.0, 0.0}; // Vermelho
static const RGB_cod cor0 = {0.0, 0.0, 0.0}; // Preto

uint32_t gera_binario_rgb_c(double red, double green, double blue);

// Frames 
Matriz_leds_config frame0_c = {
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame1_c = {
    {cor_vermelha, cor0, cor0, cor0, cor0},
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor0, cor0, cor_vermelha, cor0, cor0},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor0, cor0, cor_vermelha},
};

// Adicione mais frames conforme necessário...
Matriz_leds_config frame2_c = {
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor_vermelha, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame3_c = {
    {cor0, cor0, cor0, cor0, cor_vermelha},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor_vermelha, cor0, cor0},
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor_vermelha, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame4_c = {
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

void imprime_desenho_c(Matriz_leds_config configuracao, PIO pio, uint sm) {
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--) {
        if (contadorLinha % 2) {
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++) {
                uint32_t valor_cor_binario = gera_binario_rgb_c(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        } else {
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--) {
                uint32_t valor_cor_binario = gera_binario_rgb_c(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

uint32_t gera_binario_rgb_c(double red, double green, double blue){
    unsigned char RED, GREEN, BLUE;
    RED = red * 255.0;
    GREEN = green * 255.0;
    BLUE = blue * 255.0;
    return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

void rodar_todos_frames_c(PIO pio, uint sm) {
    int valor_delay = 200; // Delay entre os frames

    imprime_desenho_c(frame0_c, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho_c(frame1_c, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho_c(frame2_c, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho_c(frame3_c, pio, sm);
    sleep_ms(valor_delay);
}
