#include <stdio.h>

int encontrarMaior(int vetor[], int tamanho)
{
    int maior = vetor[0];
    int i;

    for (i = 1; i < tamanho; i++)
    {
        if (vetor[i] > maior)
        {
            maior = vetor[i];
        }
    }

    return maior;
}

int main()
{
    int vetor[] = {10, 5, 8, 20, 99, 233, 0, 94, 15}; // Exemplo de vetor
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);   // Calcula o tamanho do vetor
    int maior_valor = encontrarMaior(vetor, tamanho);

    printf("Vetor: [");
    int i = 0;
    for (i; i < tamanho; i++)
    {
        printf(" %d ", vetor[i]);
    }
    printf(" ]");

    printf("\nO maior valor no vetor eh: %d\n", maior_valor);

    return 0;
}
