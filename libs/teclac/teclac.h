#ifndef TECLAC_H
#define TECLAC_H

// Criando estrutura struct para controlar a cor dos LEDS
typedef struct {
    double red;
    double green;
    double blue;
}RGB_3c;

typedef RGB_3c RGB_cod_3c;
typedef RGB_3c Matriz_leds_config_3c[5][5]; 

uint32_t gera_binario_rgb_3c(double red, double green, double blue);

void imprime_desenho_3c(Matriz_leds_config_3c configuracao, PIO pio, uint sm);

void desenho_tecla_3c(bool entrada, PIO pio, uint sm);
#endif
