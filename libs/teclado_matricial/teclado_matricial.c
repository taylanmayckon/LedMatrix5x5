#include "pico/stdlib.h"
#include "teclado_matricial.h"

// GPIO utilizada para o teclado matricial
int pins_matrix_r[4] = {8, 7, 6, 5};  // Em ordem: R1, R2, R3, R4
int pins_matrix_c[4] = {4, 3, 2, 28}; // Em ordem: C1, C2, C3, C4

// Mapeamento do teclado
char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void set_rows_output(){
  for (int i=0; i<4; i++){
    gpio_init(pins_matrix_r[i]);
    gpio_set_dir(pins_matrix_r[i], GPIO_OUT);
    gpio_put(pins_matrix_r[i], 0);
  }
}

void set_cols_input(){
  for (int i=0; i<4; i++){
    gpio_init(pins_matrix_c[i]);
    gpio_set_dir(pins_matrix_c[i], GPIO_IN);
  }
}

char detect_button(){
  // Loop externo (varredura das linhas)
  for(int i=0; i<4; i++){
    // Leva a linha a ser varrida à nível alto para detecção das colunas em seguida
    gpio_put(pins_matrix_r[i], 1);
    // Loop interno (varredura das colunas)
    for(int j=0; j<4; j++){
      // Detecta se alguma coluna, correspondente à linha da iteração, está em nível alto
      if (gpio_get(pins_matrix_c[j]) == 1){
        // Se estiver, leva a linha de volta a 0 e retorna a tecla através do mapeamento do teclado
        gpio_put(pins_matrix_r[i], 0);
        return KEY_MAP[i][j];
      }
    }
    // Se nenhuma coluna for detectada, retorna a linha varrida à nível baixo
    gpio_put(pins_matrix_r[i], 0);
  }
  // Se nada for detectado, retorna o caracter ' ', um espaço vazio
  return ' ';
}