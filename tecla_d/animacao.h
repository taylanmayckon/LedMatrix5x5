// led_animation.h
#ifndef ANIMACAO_H
#define ANIMACAO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"


#include "pio_matrix.pio.h"

// // Initializes the LED matrix
// void init_led_matrix();

// // Updates the LED matrix with the current data
// void imprimir_binario(int num);

// // Runs the predefined animation
// static void gpio_irq_handler(uint gpio, uint32_t events);

// Initializes the keypad
uint32_t matrix_rgb(double b, double r, double g);

// Checks if a specific key is pressed
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

// Main loop to monitor keypad and run animations
void main_animacao(bool tecla_d, PIO pio, uint sm);

#endif // LED_ANIMATION_H
