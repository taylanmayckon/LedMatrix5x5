#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "animação_c.h"

static const RGB_cod cor_vermelha = {1.0, 0.0, 0.0}; // Vermelho
static const RGB_cod cor0 = {0.0, 0.0, 0.0}; // Preto

// Frames 
Matriz_leds_config frame0 = {
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame1 = {
    {cor_vermelha, cor0, cor0, cor0, cor0},
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor0, cor0, cor_vermelha, cor0, cor0},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor0, cor0, cor_vermelha},
};

// Adicione mais frames conforme necessário...
Matriz_leds_config frame2 = {
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor_vermelha, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame3 = {
    {cor0, cor0, cor0, cor0, cor_vermelha},
    {cor0, cor0, cor0, cor_vermelha, cor0},
    {cor0, cor0, cor_vermelha, cor0, cor0},
    {cor0, cor_vermelha, cor0, cor0, cor0},
    {cor_vermelha, cor0, cor0, cor0, cor0},
};

Matriz_leds_config frame4 = {
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
    {cor0, cor0, cor0, cor0, cor0},
};

void imprime_desenho(Matriz_leds_config configuracao, PIO pio, uint sm) {
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--) {
        if (contadorLinha % 2) {
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++) {
                uint32_t valor_cor_binario = gera_binario_rgb(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        } else {
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--) {
                uint32_t valor_cor_binario = gera_binario_rgb(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

void rodar_todos_frames(PIO pio, uint sm) {
    int valor_delay = 200; // Delay entre os frames

    imprime_desenho(frame0, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho(frame1, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho(frame2, pio, sm);
    sleep_ms(valor_delay);

    imprime_desenho(frame3, pio, sm);
    sleep_ms(valor_delay);

