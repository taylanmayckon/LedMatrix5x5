#include "pico/stdlib.h"
#include "teclado_matricial.h"
#include "pico/matrix.h" 

#define NUM_LEDS 25 // Total de LEDs na matriz 5x5

void setup() {
    stdio_init_all();
    set_rows_output();
    set_cols_input();
    matrix_init(); // Inicializa a matriz de LEDs
}

// led em vermelho
void animate_red_pulse() {
    for (int i = 0; i < 5; i++) {
        int intensity = (5 - i) * 51; // Intensidade de 255 a 0
        matrix_fill_color(intensity, 0, 0); // Preenche a matriz com a cor vermelha
        sleep_ms(200); // Espera 200 ms entre os frames
    }
}

void loop() {
    char key = detect_button();
    
    if (key == 'C') {
        animate_red_pulse(); 
    }

}

int main() {
    setup();
    while (true) {
        loop();
    }
}
