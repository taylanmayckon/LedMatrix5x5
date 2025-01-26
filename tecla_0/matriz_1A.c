#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/clocks.h"
#include "matriz_1A.pio.h"
#include "libs/teclado_matricial/teclado_matricial.h"

// número de LEDs
#define NUM_PIXELS 25
// pino de saída
#define OUT_PIN 7

// Frames de animações
double frame1[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                     0.0, 0.3, 0.0, 0.3, 0.0,
                     0.0, 0.0, 0.0, 0.0, 0.0,
                     0.3, 0.3, 0.3, 0.3, 0.3,
                     0.0, 0.0, 0.0, 0.0, 0.0};

double frame2[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                     0.0, 0.3, 0.0, 0.3, 0.0,
                     0.0, 0.0, 0.0, 0.0, 0.0,
                     0.3, 0.0, 0.0, 0.0, 0.3,
                     0.0, 0.3, 0.3, 0.3, 0.0};

double frame3[25] = {0.3, 0.3, 0.3, 0.3, 0.3,
                     0.3, 0.0, 0.0, 0.0, 0.3,
                     0.3, 0.0, 0.3, 0.0, 0.3,
                     0.3, 0.0, 0.0, 0.0, 0.3,
                     0.3, 0.3, 0.3, 0.3, 0.3};

double frame4[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                     0.0, 0.3, 0.0, 0.3, 0.0,
                     0.0, 0.0, 0.0, 0.0, 0.0,
                     0.3, 0.0, 0.0, 0.0, 0.3,
                     0.0, 0.3, 0.3, 0.3, 0.0};

double frame5[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                     0.0, 0.3, 0.0, 0.3, 0.0,
                     0.0, 0.0, 0.0, 0.0, 0.0,
                     0.3, 0.0, 0.0, 0.0, 0.3,
                     0.0, 0.3, 0.3, 0.3, 0.0};

double off[25] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

// Conversão de valores RGB para o protocolo WS2812
uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 16) | (R << 24) | (B << 8);
}

// Desenho da matriz utilizando a PIO
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        valor_led = matrix_rgb(b, desenho[24 - i], g);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

int main()
{
    // Inicializa os sistemas do Pico
    stdio_init_all();

    // Configurações do sistema
    PIO pio = pio0;
    double r = 0.0, b = 0.0, g = 0.0;
    uint32_t valor_led;

    // Configuração do clock do sistema
    set_sys_clock_khz(128000, false);

    // Configurações da PIO para controlar os LEDs WS2812
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while (true)
    {
        // Detecta a tecla pressionada no teclado matricial
        char key = detect_button();

        if (key == '0') // Se a tecla '0' for pressionada, exibe uma sequência de frames
        {
            desenho_pio(frame1, valor_led, pio, sm, r, g, b);
            sleep_ms(1000);
            desenho_pio(frame2, valor_led, pio, sm, r, g, b);
            sleep_ms(1000);
            desenho_pio(frame3, valor_led, pio, sm, r, g, b);
            sleep_ms(1000);
            desenho_pio(frame4, valor_led, pio, sm, r, g, b);
            sleep_ms(1000);
            desenho_pio(frame5, valor_led, pio, sm, r, g, b);
            sleep_ms(1000);
            desenho_pio(off, valor_led, pio, sm, r, g, b);
            sleep_ms(3000);
        }
    }
}
