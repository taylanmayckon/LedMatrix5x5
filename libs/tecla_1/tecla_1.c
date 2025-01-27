#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "tecla_1.h"

// Arquivo .pio para controle da matriz
#include "pio_matrix.pio.h"

// Pino que realizará a comunicação do microcontrolador com a matriz
#define OUT_PIN 7

// Definindo os vetores das cores
static const RGB_cod cor1 = {163/255.0, 36/255.0,  61/255.0};
static const RGB_cod cor2 = {223/255.0, 85/255.0,  40/255.0};
static const RGB_cod cor3 = {233/255.0, 171/255.0, 62/255.0};
static const RGB_cod cor4 = {241/255.0, 218/255.0, 92/255.0};
static const RGB_cod cor5 = {107/255.0, 199/255.0, 127/255.0};
static const RGB_cod cor6 = {147/255.0, 231/255.0, 242/255.0};
static const RGB_cod cor7 = {113/255.0, 93/255.0,  244/255.0};
static const RGB_cod cor8 = {106/255.0, 48/255.0,  138/255.0};
static const RGB_cod cor9 = {162/255.0, 82/255.0,  182/255.0};

Matriz_leds_config frame1 = {
//Cols    0     1      2     3    4
        {cor1, cor2, cor3, cor4, cor5}, // Linha 0
        {cor2, cor3, cor4, cor5, cor6}, // Linha 1
        {cor3, cor4, cor5, cor6, cor7}, // Linha 2
        {cor4, cor5, cor6, cor7, cor8}, // Linha 3
        {cor5, cor6, cor7, cor8, cor9}, // Linha 4
};

uint32_t gera_binario_rgb(double red, double green, double blue){
    unsigned char RED, GREEN, BLUE;
    RED = red * 255.0;
    GREEN = green * 255.0;
    BLUE = blue * 255.0;
    return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

void imprime_desenho(Matriz_leds_config configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = gera_binario_rgb(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
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


void desenho_tecla1(PIO pio, uint sm){
    while(true){
    imprime_desenho(frame1, pio, sm);
    sleep_ms(1000);
    }
}
