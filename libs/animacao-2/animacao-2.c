#include "animacao-2.h"

// Frames da animação
static double frame1[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0
};

static double frame2[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0
};

static double frame3[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.1, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0
};

static double frame4[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.1, 0.0, 0.1, 0.0, 0.1,
    0.1, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0
};

static double frame5[25] = {
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.1, 0.0, 0.1, 0.0, 0.1,
    0.1, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0
};

static double off[25] = {0.0};

// Função para converter cores em 32 bits
static uint32_t matrix_rgb(double b, double r, double g) {
    return ((uint32_t)(g * 255) << 24) | ((uint32_t)(r * 255) << 16) | ((uint32_t)(b * 255) << 8);
}

// Função para desenhar um frame na matriz
static void desenho_pio(double *desenho, PIO pio, uint sm) {
    uint32_t valor_led;
    for (int i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, desenho[24 - i], 0.0);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função principal da animação
void executar_animacao(PIO pio, uint sm) {
    desenho_pio(frame1, pio, sm);
    sleep_ms(500);
    desenho_pio(frame2, pio, sm);
    sleep_ms(500);
    desenho_pio(frame3, pio, sm);
    sleep_ms(500);
    desenho_pio(frame4, pio, sm);
    sleep_ms(500);
    desenho_pio(frame5, pio, sm);
    sleep_ms(500);
    desenho_pio(off, pio, sm);
    sleep_ms(500);
}
