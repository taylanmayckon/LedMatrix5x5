#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/clocks.h"
#include "matriz-led.pio.h"
#include "libs\teclado_matricial\teclado_matricial.h"

// número de LEDs
#define NUM_PIXELS 25
// pino de saída
#define OUT_PIN 7

double leds[25] = {
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
};

uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void leds_pio(double *leds, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        valor_led = matrix_rgb(leds[24 - i], r = 0.0, g = 0.0);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

int main()
{
    stdio_init_all();

    PIO pio = pio0;
    double r = 0.0, b = 0.0, g = 0.0;
    uint32_t valor_led;

    // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    set_sys_clock_khz(128000, false);

    // configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while (true)
    {
        if (detect_button() == 'B')
        {
            leds_pio(leds, valor_led, pio, sm, r, g, b);
        }
    }
}