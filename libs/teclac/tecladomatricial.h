#ifndef TECLADO_MATRICIAL_H
#define TECLADO_MATRICIAL_H

// GPIO utilizada para o teclado matricial
int pins_matrix_r[4];
int pins_matrix_c[4];

void set_rows_output();
void set_cols_input();
char detect_button();

#endif

#include "pico/stdlib.h"
#include "teclado_matricial.h"

// GPIO utilizada para o teclado matricial
int pins_matrix_r[4] = {28, 27, 26, 22};  // Em ordem: R1, R2, R3, R4
int pins_matrix_c[4] = {21, 20, 19, 18}; // Em ordem: C1, C2, C3, C4

char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void set_rows_output() {
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_matrix_r[i]);
        gpio_set_dir(pins_matrix_r[i], GPIO_OUT);
        gpio_put(pins_matrix_r[i], 0);
    }
}

void set_cols_input() {
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_matrix_c[i]);
        gpio_set_dir(pins_matrix_c[i], GPIO_IN);
    }
}

char detect_button() {
    for (int i = 0; i < 4; i++) {
        gpio_put(pins_matrix_r[i], 1); // Ativa a linha
        for (int j = 0; j < 4; j++) {
            if (gpio_get(pins_matrix_c[j]) == 1) { // Verifica se a coluna está ativa
                gpio_put(pins_matrix_r[i], 0); // Desativa a linha
                return KEY_MAP[i][j]; // Retorna a tecla pressionada
            }
        }
        gpio_put(pins_matrix_r[i], 0); // Desativa a linha
    }
    return ' ';
}