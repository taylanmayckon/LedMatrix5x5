#ifndef TECLADO_MATRICIAL_H
#define TECLADO_MATRICIAL_H

// Funções para configurar a GPIO do teclado matricial
void set_rows_output();
void set_cols_input();

// Função de detecção da tecla pressionada
char detect_button();

#endif