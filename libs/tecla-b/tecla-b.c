#include "tecla-b.h"

// Array de LEDs inicializados com 1
static double leds[NUM_PIXELS] = {
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1
};

// Converte valores de cor para o formato 32 bits
static uint32_t matrix_rgb(double b, double r, double g) {
    return ((uint32_t)(g * 255) << 24) | ((uint32_t)(r * 255) << 16) | ((uint32_t)(b * 255) << 8);
}

// Liga os LEDs azuis na matriz quando a tecla 'B' é pressionada
void ligar_leds_verdes(PIO pio, uint sm) {
    uint32_t valor_led;
    for (int i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(leds[24 - i], 0.0, 1.0); // Somente canal azul ativo
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}
