#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

// Definições dos desenhos com animações (matrizes 5x5 com valores 0.0 para os LEDs apagados)
double desenho1[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.3, 0.0, 0.3, 0.0, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.0, 0.3,
                       0.0, 0.3, 0.3, 0.3, 0.0};

double desenho2[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.3, 0.0, 0.0, 0.0, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.0, 0.3,
                       0.0, 0.3, 0.3, 0.3, 0.0};

double desenho3[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.3, 0.0, 0.3, 0.0, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.0, 0.3,
                       0.0, 0.3, 0.3, 0.3, 0.0};

double desenho4[25] = {0.0, 0.3, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.3, 0.0, 
                       0.3, 0.0, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.3, 0.0,
                       0.0, 0.3, 0.0, 0.0, 0.0};

double desenho5[25] = {0.0, 0.3, 0.3, 0.3, 0.0,
                       0.3, 0.0, 0.0, 0.0, 0.3, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.3, 0.0, 0.3, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0};

double desenho6[25] = {0.0, 0.0, 0.0, 0.3, 0.0,
                       0.0, 0.3, 0.0, 0.0, 0.3, 
                       0.0, 0.0, 0.0, 0.0, 0.3,
                       0.0, 0.3, 0.0, 0.0, 0.3,
                       0.0, 0.0, 0.0, 0.3, 0.0};

double desenho7[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.3, 0.0, 0.3, 0.0, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.3, 0.0, 0.0, 0.0, 0.3,
                       0.0, 0.3, 0.3, 0.3, 0.0};

double desenho8[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0};

// Função para detectar a tecla pressionada
char detect_button(void) {
    // Colocar o código para detectar a tecla pressionada, por exemplo, do teclado matricial
    // Retorna o char da tecla pressionada (exemplo: 'A', '0', etc.)
}

// Função para acionar os LEDs
void led_matrix_draw_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = led_matrix_rgb(b=0.0, r=0.0, desenho[24-i]);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função para definir a cor do LED
uint32_t led_matrix_rgb(double b, double r, double g) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função principal que executa a animação
void led_matrix_main_animation(char tecla, PIO pio, uint sm) {
    uint32_t valor_led;
    double r = 0.0, b = 0.0, g = 0.0;

    if (tecla == 'A') {
        led_matrix_draw_pio(desenho8, valor_led, pio, sm, r, g, b); // Desliga todos os LEDs
    } 
    else if (tecla == '0') {
        for (int16_t i = 0; i < 7; i++) {
            switch (i) {
                case 0:
                    led_matrix_draw_pio(desenho1, valor_led, pio, sm, r, g, b);
                    break;
                case 1:
                    led_matrix_draw_pio(desenho2, valor_led, pio, sm, r, g, b);
                    break;
                case 2:
                    led_matrix_draw_pio(desenho3, valor_led, pio, sm, r, g, b);
                    break;
                case 3:
                    led_matrix_draw_pio(desenho4, valor_led, pio, sm, r, g, b);
                    break;
                case 4:
                    led_matrix_draw_pio(desenho5, valor_led, pio, sm, r, g, b);
                    break;
                case 5:
                    led_matrix_draw_pio(desenho6, valor_led, pio, sm, r, g, b);
                    break;
                default:
                    led_matrix_draw_pio(desenho7, valor_led, pio, sm, r, g, b);
                    break;
            }
            sleep_ms(500);
        }
    }
}
