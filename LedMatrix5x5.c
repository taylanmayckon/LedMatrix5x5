#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/clocks.h"
#include "matriz-led.pio.h"
#include "animacao-2.h"
#include "libs/teclado_matricial/teclado_matricial.h"

int main() {
    stdio_init_all();

    PIO pio = pio0;
    set_sys_clock_khz(128000, false); // Define clock para 128 MHz

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while (true) {
        if (detect_button() == '2') {
            executar_animacao(pio, sm);
        }
    }
}
