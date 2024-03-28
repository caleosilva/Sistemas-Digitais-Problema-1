#include <stdio.h>
#include <stdlib.h>
//#include "IntelFPGAUP/LEDR.h"
//#include "IntelFPGAUP/SW_H.h"
//#ifndef LEDR_H
//#define LEDR_H
//#ifndef SW_H
//#define SW_H

// Funcao para configurar LEDs com base no vetor de estado
void LEDR_set_sequence(char *binario) {
    int i;
    int indice; // Indice do LED
    int tamanho = strlen(binario);

    // Abre o dispositivo de LED
    // LEDR_open();
    
    // Percorre a string binária de tras para frente
    for (i = tamanho - 1; i >= 0; i--) {
        // Se o caractere for '1', liga o LED correspondente
        if (binario[i] == '1') {
            indice = tamanho - 1 - i; // Inverte o indice
            printf("LED ligado no índice %d \n", indice);
            // LEDR_set(indice);
        }
    }

    // Fecha o dispositivo de LED
    // LEDR_close();
}


// Função para converter um numero decimal para binario e retornar como uma string
char* num_bin_converter(int num) {
    // Aloca memoria para a string binaria
    char* binario = (char*)malloc(33 * sizeof(char)); // 32 bits + terminador de string
    int i;

    // Caso base: se o numero for zero, retorna "0" diretamente
    if (num == 0) {
        binario[0] = '0';
        binario[1] = '\0'; // Terminador de string
        return binario;
    }

    // Converte o número decimal para binario
    for (i = 31; i >= 0; i--) {
        binario[i] = (num & 1) + '0'; // Converte o digito binario para o caractere correspondente
        num >>= 1; // Desloca o numero para a direita para processar o próximo bit
    }
    binario[32] = '\0'; // Terminador de string

    return binario;
}

// Funcao para encontrar o maior valor em um vetor de inteiros
int encontrarMaior(int vetor[], int tamanho) {
    int maior = vetor[0];
    int i;

    for (i = 1; i < tamanho; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    return maior;
}

int main() {
    int vetor[] = {10, 5, 8, 20, 99, 233, 0, 94, 15}; // Exemplo de vetor
    int tamanho = sizeof(vetor) / sizeof(vetor[0]); // Calcula o tamanho do vetor
    int maior_valor = encontrarMaior(vetor, tamanho); // Encontra o maior valor no vetor
    char* binario; // String binária
    int i;
    int SW_status;
    
    printf("O maior valor no vetor é: %d\n", maior_valor);

    // Converte o maior valor para binário
    binario = num_bin_converter(maior_valor);
    printf("O maior valor em binário é: %s\n", binario);
    
    // Converte a representação binária de volta para um vetor de inteiros
    int leds[32]; // Supondo que o número máximo de LEDs seja 32
    for (i = 0; i < 32; i++) {
        leds[i] = binario[i] - '0'; // Converte o caractere '0' ou '1' em um valor inteiro
    }
    
    
//	int SW_open (void);
//	SW_status =  SW_read (1); //Verifica o status da chave
//	void SW_close (void);
	
	if (SW_status == 1) {
    	LEDR_set_sequence(binario); // Configura os LEDs com base no vetor de binarios
	}
    
    free(binario); // Libera a memória alocada para a string binária
    return 0;
}
