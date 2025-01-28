#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/teclado_matricial/teclado_matricial.h"
#include "libs/tecla_d/animacao.h"
#include "libs/tecla_jogo_velha/tecla_jogo_velha.h"
#include "libs/tecla_1/tecla_1.h"
#include "libs/tecla_A/led_animation.h"

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
        switch (tecla) {
            case '0':
                led_matrix_main_animation(tecla, pio, sm);
                break;
            case '1':
                desenho_tecla1(pio, sm);
                break;
            case '4':
                main_animacao(false, pio, sm);
                break;
            case '5':
                gera_animacao(tecla, pio, sm);
                break;
            case 'A':
                led_matrix_main_animation(tecla, pio, sm);
                break;
            case 'D':
                main_animacao(true, pio, sm);
                break;
            case '#':
                gera_animacao(tecla, pio, sm);
                break;
        }
        sleep_ms(100); // Delay para evitar múltiplas leituras rápidas
    }
}
