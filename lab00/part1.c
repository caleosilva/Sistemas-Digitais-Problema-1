#include <stdio.h>

int encontrarMaior(int vetor[], int tamanho) {
    int maior = vetor[0]; // Assumimos que o primeiro elemento é o maior inicialmente
    int i; // Declaração de i aqui
    
    for (i = 1; i < tamanho; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i]; // Se encontrarmos um número maior, atualizamos o valor de "maior"
        }
    }
    
    return maior;
}

int main() {
    int vetor[] = {10, 5, 8, 20, 99, 233, 0, 94, 15}; // Exemplo de vetor
    int tamanho = sizeof(vetor) / sizeof(vetor[0]); // Calcula o tamanho do vetor
    int maior_valor = encontrarMaior(vetor, tamanho); // Chama a função para encontrar o maior valor
    
    printf("O maior valor no vetor eh: %d\n", maior_valor);
    
    return 0;
}

