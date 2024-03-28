#include <stdio.h>
#include <unistd.h> // Para a função usleep
#include "IntelFPGAUP/LEDR.h"

#ifndef LEDR_H
#define LEDR_H

// Função para ligar/desligar os LEDs sequencialmente
void LEDR_set_sequence(int num_leds) {
    
    int i;
    // Abre o dispositivo de LED
    LEDR_open();
    
    // Loop principal que alterna entre contagem crescente e decrescente
    while (1) {
        // Contagem crescente de 0 a num_leds
        for (i = 0; i < num_leds; i++) {
            // Liga o LED correspondente
            LEDR_set(i);
            usleep(700000); // Pausa de 700ms
        }
        
        // Contagem decrescente de num_leds a 0
        for (i = num_leds - 1; i >= 0; i--) {
            // Liga o LED correspondente
            LEDR_set(i);
            usleep(700000); // Pausa de 700ms
        }
    }
    
    // Fecha o dispositivo de LED
    LEDR_close();
}

#endif

int main(void) {

    LEDR_set_sequence(10); // Todos os LEDs ligados sequencialmente
    return 0;
}
