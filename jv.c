#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>


#include <fcntl.h>
#include <pthread.h>

#define LINHAS 3
#define COLUNAS 3

//* PARTE DO MOUSE INICIO
// Variáveis globais para armazenar movimentos e cliques do mouse
int dx = 0;
int dy = 0;
int botaoEsquerdo = 0;
int botaoDireito = 0;
int botaoMeio = 0;

// Variáveis globais para armazenar os valores anteriores de movimento e cliques do mouse

int dxAnterior = 0;
int dyAnterior = 0;
int botaoEsquerdoAnterior = 0;
int botaoDireitoAnterior = 0;
int botaoMeioAnterior = 0;

int linha = 2, coluna = 3;

void *monitorarMouse(void *arg) {
    int fd;
    char *mouse_device = "/dev/input/mice";
    signed char data[3];

    fd = open(mouse_device, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o dispositivo do mouse");
        return NULL;
    }

    while(1) {
        read(fd, data, sizeof(data));

        // Armazena os movimentos do mouse e o estado dos botões nas variáveis globais
        dx = data[1];
        dy = data[2];
        botaoEsquerdo = data[0] & 0x01;
        botaoDireito = data[0] & 0x02;
        botaoMeio = data[0] & 0x04;

        // Intervalo de atualização
        usleep(1500000); // 100 ms
    }

    close(fd);
    return NULL;
}

//* PARTE DO JOGO DA VELHA INICIO
// Estrutura para representar o tabuleiro do jogo da velha
char tabuleiro[LINHAS][COLUNAS];

// Funcao para inicializar o tabuleiro do jogo da velha com espacos vazios
void inicializar_tabuleiro() {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Funcao para desenhar o tabuleiro do jogo da velha
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

// Funcao para colocar um simbolo (X ou O) em uma posicao especificada
int colocar_simbolo(int linha, int coluna, char simbolo) {
    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS) {
        printf("Posicao invalida!\n");
        return 0;
    }
    if (tabuleiro[linha][coluna] != ' ') {
        printf("Posicao ja ocupada!\n");
        return 0;
    }
    tabuleiro[linha][coluna] = simbolo;
    return 1;
}

// Funcao para verificar se algum jogador ganhou
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

    // Se nao houver vencedor
    return ' ';
}

// Funcao para verificar se houve um empate
int verificar_empate() {
    int i, j;

    // Verificar se todas as colulas estao preenchidas
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0; // Ainda ha colunas vazias, o jogo nao estao empatado
        }
    }

    // Se todas as colunas estiverem preenchidas e nao houver vencedor, ha um empate
    return 1;
}

// Funcao para perguntar ao jogador em qual posicao ele deseja colocar seu simbolo
void escolher_quadrante(char simbolo) {

    int jogada_feita = 0; // Variável para controlar se o jogador fez uma jogada
    int confirmar_jogada = 0;

    while (!jogada_feita) {

        // Verifica se houve mudança nos valores do mouse desde a última impressão
        if (dx != dxAnterior || dy != dyAnterior || botaoEsquerdo != botaoEsquerdoAnterior || botaoDireito != botaoDireitoAnterior || botaoMeio != botaoMeioAnterior) {
            // Se houve mudança, atualiza os valores anteriores e imprime as informações do mouse
            // Mostra as coordenadas atualizadas
                printf("COORDENADAS: %i -- %i\n", linha, coluna);

            // Atualiza as coordenadas do quadrante com base no movimento do mouse
            if (dy < 0 && linha > 1) {
                linha--;
            } else if (dy > 0 && linha < 3) {
                linha++;
            }

            else if (dx < 0 && coluna > 1) {
                coluna--;
            } else if (dx > 0 && coluna < 3) {
                coluna++;
            }
            else if (botaoEsquerdo & 0x01){
                confirmar_jogada = 1;
            }

            dxAnterior = dx;
            dyAnterior = dy;
            botaoEsquerdoAnterior = botaoEsquerdo;
            botaoDireitoAnterior = botaoDireito;
            botaoMeioAnterior = botaoMeio;


            if (confirmar_jogada == 1) {
                // Verifica se o jogador fez uma jogada válida e sai do loop
                if (colocar_simbolo(linha - 1, coluna - 1, simbolo)) {
                    desenhar_tabuleiro();
                    jogada_feita = 1; // Define que o jogador fez uma jogada válida
                }
                confirmar_jogada = 0;
            }
        }
    }
}






int main() {

    pthread_t threadMouse;

    if (pthread_create(&threadMouse, NULL, monitorarMouse, NULL)) {
        fprintf(stderr, "Erro ao criar a thread do mouse\n");
        return 1;
    }

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

    // Variavel para alternar entre X e O
    char jogador = 'X';

    // Loop principal do jogo
    while (1) {




        printf("Jogador %c, eh sua vez!\n", jogador);

        escolher_quadrante(jogador);


        // Verificar se algum jogador ganhou
        char vencedor = verificar_vencedor();
        if (vencedor != ' ') {
            printf("Parabens! O jogador %c venceu!\n", vencedor);
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
        // Outras tarefas do programa principal, se necessário
        //usleep(50000); // 1 segundo
    }

    return 0;
}
