#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/teclado_matricial/teclado_matricial.h"
#include "tecla_d/animacao.h"


int main()
{
    stdio_init_all();

    set_rows_output();
    set_cols_input();

    while (true) {
        char tecla = detect_button(); // Armazena a tecla detectada
        printf("Tecla pressionada: %c\n", tecla);

        if (tecla == '4') {
            main_animacao(false); // Aciona o buzzer
        }
        else if (tecla == 'D') 
        {
            main_animacao(true);
        }

        sleep_ms(50); // Delay para evitar múltiplas leituras rápidas
    }
}
