#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "teclac.h"

// Arquivo .pio para controle da matriz
#include "pio_matrix.pio.h"

// Pino que realizará a comunicação do microcontrolador com a matriz
#define OUT_PIN 7

// Definindo os vetores das cores
static const RGB_cod_3c cor1 = {255.0/255.0, 0.0, 0.0};

static const RGB_cod_3c cor0 = {0, 0, 0};

// Frames de animação
Matriz_leds_config_3c frame_red = {
    {cor1, cor1, cor1, cor1, cor1}, // Linha 0
    {cor1, cor1, cor1, cor1, cor1}, // Linha 1
    {cor1, cor1, cor1, cor1, cor1}, // Linha 2
    {cor1, cor1, cor1, cor1, cor1}, // Linha 3
    {cor1, cor1, cor1, cor1, cor1}, // Linha 4
};


Matriz_leds_config_3c frame1_3c = {
//Cols    0     1      2     3    4
        {cor1, cor1, cor1, cor1, cor1}, // Linha 0
        {cor1, cor0, cor0, cor0, cor0}, // Linha 1
        {cor1, cor1, cor1, cor1, cor1}, // Linha 2
        {cor0, cor0, cor0, cor0, cor1}, // Linha 3
        {cor1, cor1, cor1, cor1, cor1}, // Linha 4
};

Matriz_leds_config_3c frame2_3c = {
    {cor1, cor1, cor1, cor1, cor1}, // Linha 0
    {cor1, cor0, cor0, cor0, cor1}, // Linha 1
    {cor1, cor0, cor0, cor0, cor1}, // Linha 2
    {cor1, cor0, cor0, cor0, cor1}, // Linha 3
    {cor1, cor1, cor1, cor1, cor1}, // Linha 4
};

Matriz_leds_config_3c frame3_3c = {
    {cor1, cor1, cor1, cor1, cor0}, // Linha 0
    {cor1, cor0, cor0, cor1, cor0}, // Linha 1
    {cor1, cor1, cor1, cor1, cor0}, // Linha 2
    {cor1, cor0, cor0, cor0, cor0}, // Linha 3
    {cor1, cor0, cor0, cor0, cor0}, // Linha 4
};

Matriz_leds_config_3c frame4_3c = {
    {cor1, cor0, cor0, cor0, cor1}, // Linha 0
    {cor1, cor0, cor0, cor0, cor1}, // Linha 1
    {cor1, cor1, cor1, cor1, cor1}, // Linha 2
    {cor1, cor0, cor0, cor0, cor1}, // Linha 3
    {cor1, cor0, cor0, cor0, cor1}, // Linha 4
};

Matriz_leds_config_3c frame5_3c = {
    {cor0, cor1, cor1, cor1, cor0}, // Linha 0
    {cor0, cor0, cor1, cor0, cor0}, // Linha 1
    {cor0, cor0, cor1, cor0, cor0}, // Linha 2
    {cor0, cor0, cor1, cor0, cor0}, // Linha 3
    {cor0, cor1, cor1, cor1, cor0}, // Linha 4
};

Matriz_leds_config_3c frame6_3c = {
    {cor1, cor1, cor1, cor1, cor1}, // Linha 0
    {cor1, cor0, cor0, cor0, cor1}, // Linha 1
    {cor1, cor0, cor0, cor0, cor1}, // Linha 2
    {cor1, cor1, cor1, cor1, cor1}, // Linha 3
    {cor1, cor0, cor0, cor0, cor1}, // Linha 4
};

Matriz_leds_config_3c frame7_3c = {
    {cor0, cor0, cor0, cor0, cor0}, // Linha 0
    {cor0, cor0, cor0, cor0, cor0}, // Linha 1
    {cor0, cor0, cor0, cor0, cor0}, // Linha 2
    {cor0, cor0, cor0, cor0, cor0}, // Linha 3
    {cor0, cor0, cor0, cor0, cor0}, // Linha 4
};



uint32_t gera_binario_rgb_3c(double red, double green, double blue){
    unsigned char RED, GREEN, BLUE;
    RED = red * 255.0;
    GREEN = green * 255.0;
    BLUE = blue * 255.0;
    return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

void imprime_desenho_3c(Matriz_leds_config_3c configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = gera_binario_rgb_3c(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = gera_binario_rgb_3c(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

void desenho_tecla_3c(bool entrada, PIO pio, uint sm){
    if(entrada == true){
        imprime_desenho_3c(frame1_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame2_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame3_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame4_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame5_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame6_3c, pio, sm);
        sleep_ms(600);

        imprime_desenho_3c(frame7_3c, pio, sm);
    }

    // False ele imprime o vermelho
    else if(entrada == false){
        imprime_desenho_3c(frame_red, pio, sm);
    }
}
