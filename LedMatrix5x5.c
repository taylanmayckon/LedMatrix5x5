#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/teclado_matricial/teclado_matricial.h"
#include "tecla_d/animacao.h"

#define OUT_PIN 7

void teclado_matricial_config() 
{
    stdio_init_all();

    set_rows_output();
    set_cols_input();
}

uint pio_config(PIO pio) 
{
    bool ok;
    // uint32_t valor_led;
    // double r = 0.0, b = 0.0 , g = 0.0;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    // stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    return sm;
}


int main()
{
    PIO pio = pio0; 
    uint16_t i;
    teclado_matricial_config();
    uint sm = pio_config(pio);

    while (true) {
        char tecla = detect_button(); // Armazena a tecla detectada
        printf("Tecla pressionada: %c\n", tecla);

        if (tecla == '4') {
            main_animacao(false, pio, sm); // Aciona o buzzer
        }
        else if (tecla == 'D') 
        {
            main_animacao(true, pio, sm);
        }

        sleep_ms(100); // Delay para evitar múltiplas leituras rápidas
    }
}
