#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define LINHAS 3
#define COLUNAS 3

// Estrutura para representar o tabuleiro do jogo da velha
char tabuleiro[LINHAS][COLUNAS];

// Função para inicializar o tabuleiro do jogo da velha com espaços vazios
void inicializar_tabuleiro() {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Função para desenhar o tabuleiro do jogo da velha
void desenhar_tabuleiro() {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < COLUNAS - 1)
                printf("|");
        }
        printf("\n");
        if (i < LINHAS - 1)
            printf("---|---|---\n");
    }
    printf("\n");
}

// Função para colocar um símbolo (X ou O) em uma posição especificada
int colocar_simbolo(int linha, int coluna, char simbolo) {
    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS) {
        printf("Posição inválida!\n");
        return 0;
    }
    if (tabuleiro[linha][coluna] != ' ') {
        printf("Posição já ocupada!\n");
        return 0;
    }
    tabuleiro[linha][coluna] = simbolo;
    return 1;
}

// Função para verificar se algum jogador ganhou
char verificar_vencedor() {
    int i, j;

    // Verificar linhas e colunas
    for (i = 0; i < LINHAS; i++) {
        if (tabuleiro[i][0] != ' ' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2])
            return tabuleiro[i][0];
        if (tabuleiro[0][i] != ' ' && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i])
            return tabuleiro[0][i];
    }

    // Verificar diagonais
    if (tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2])
        return tabuleiro[0][0];
    if (tabuleiro[0][2] != ' ' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0])
        return tabuleiro[0][2];

    // Se não houver vencedor
    return ' ';
}

// Função para verificar se houve um empate
int verificar_empate() {
    int i, j;

    // Verificar se todas as células estão preenchidas
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0; // Ainda há células vazias, o jogo não está empatado
        }
    }

    // Se todas as células estiverem preenchidas e não houver vencedor, é um empate
    return 1;
}

// Função para perguntar ao jogador em qual posição ele deseja colocar seu símbolo
void escolher_quadrante(char simbolo) {
    int linha, coluna;
    printf("Digite a linha (1-3): ");
    scanf("%d", &linha);
    printf("Digite a coluna (1-3): ");
    scanf("%d", &coluna);
    linha--;
    coluna--;
    if (colocar_simbolo(linha, coluna, simbolo)) {
        desenhar_tabuleiro();
    } else {
        escolher_quadrante(simbolo);
    }
}

int main() {
    struct winsize w;
    
    // Obter o tamanho do terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    // Largura e altura do terminal
    int largura_terminal = w.ws_col;
    int altura_terminal = w.ws_row;
    
    // Calcular o tamanho da grade do jogo da velha
    int tamanho_grade_largura = largura_terminal;
    int tamanho_grade_altura = altura_terminal;
    
    // Inicializar o tabuleiro do jogo da velha
    inicializar_tabuleiro();
    
    // Desenhar o tabuleiro inicial
    desenhar_tabuleiro();
    
    // Variável para alternar entre X e O
    char jogador = 'X';
    
    // Loop principal do jogo
    while (1) {
        printf("Jogador %c, é sua vez!\n", jogador);
        escolher_quadrante(jogador);
        
        // Verificar se algum jogador ganhou
        char vencedor = verificar_vencedor();
        if (vencedor != ' ') {
            printf("Parabéns! O jogador %c venceu!\n", vencedor);
            break;
        }
        
        // Verificar se houve um empate
        if (verificar_empate()) {
            printf("Empate!\n");
            break;
        }
        
        // Alternar entre X e O
        if (jogador == 'X')
            jogador = 'O';
        else
            jogador = 'X';
    }
    
    return 0;
}

