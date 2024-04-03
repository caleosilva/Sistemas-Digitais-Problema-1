#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <intelfpgaup/SW.h>
#include <intelfpgaup/LEDR.h>


// Função para encontrar o maior valor e sua posição
int encontrarMaior(int vetor[], int tamanho, int *posicao)
{
    int maior = vetor[0];
    *posicao = 0; // Inicializa a posição do maior valor como 0
    int i;

    for (i = 1; i < tamanho; i++)
    {
        if (vetor[i] > maior)
        {
            maior = vetor[i];
            *posicao = i; // Atualiza a posição do maior valor
        }
    }
    return maior;
}

int main()
{
    int vetor[] = {10, 5, 8, 20, 99, 233, 0, 94, 15}; // Exemplo de vetor
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);   // Calcula o tamanho do vetor
    int posicao_maior;
    int maior_valor = encontrarMaior(vetor, tamanho, &posicao_maior);

    printf("\nO maior valor no vetor eh: %d\n", maior_valor);
    printf("A posicao do maior valor no vetor eh: %d\n", posicao_maior);
    SW_open();

    int data;
    while (1)
    {
        SW_read(&data);

        if (data == 0b0000000001)
        {
            LEDR_open();
            LEDR_set(posicao_maior);
            LEDR_close();
        }
        else
        {
            LEDR_open();
            LEDR_set(0b0000000000);
            LEDR_close();
        }
    }
    SW_close();

    return 0;
}
