#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/clocks.h"
#include "matriz-led.pio.h"
#include "tecla-b.h"
#include "libs/teclado_matricial/teclado_matricial.h"

int main() {
    stdio_init_all();

    PIO pio = pio0;

    // Define o clock para 128 MHz
    set_sys_clock_khz(128000, false);

    // Configuração da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while (true) {
        if (detect_button() == 'B') {
            ligar_leds_verdes(pio, sm);
        }
    }
}
