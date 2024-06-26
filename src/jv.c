#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <fcntl.h>
#include <pthread.h>

#define LINHAS 3
#define COLUNAS 3
#define LIMITE_DESLOCAMENTO 5 // Define o limite mínimo de deslocamento necessário

//* PARTE DO MOUSE INICIO

// Jogador da vez
char jogador = 'X';
int playing = 1;
int recomecar = 0;
int pauseGame = 0;
int onMenu = 1;
int stop = 0;

// Variáveis globais para armazenar movimentos e cliques do mouse
int raw_dx = 0;
int raw_dy = 0;
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

char tabuleiro[LINHAS][COLUNAS];
char copia[LINHAS][COLUNAS];

// int linha = 2, coluna = 2;

typedef struct
{
    int linha;
    int coluna;
    int rightClick;
} InputMouse;

void *monitorarMouse(void *arg)
{
    int fd;
    char *mouse_device = "/dev/input/mice";
    signed char data[3];

    fd = open(mouse_device, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o dispositivo do mouse");
        return NULL;
    }

    while (playing)
    {
        read(fd, data, sizeof(data));
        raw_dx = data[1];
        raw_dy = data[2];
        botaoEsquerdo = data[0] & 0x01;
        botaoDireito = data[0] & 0x02;
        botaoMeio = data[0] & 0x04;

        dx = 0;
        dy = 0;

        if (abs(raw_dx) >= abs(raw_dy))
        {
            if (raw_dx > LIMITE_DESLOCAMENTO)
                dx = 1;
            else if (raw_dx < -LIMITE_DESLOCAMENTO)
                dx = -1;
        }
        else if (abs(raw_dy) > abs(raw_dx))
        {
            if (raw_dy > LIMITE_DESLOCAMENTO)
                dy = 1;
            else if (raw_dy < -LIMITE_DESLOCAMENTO)
                dy = -1;
        }
    }

    close(fd);
    return NULL;
}

// Funcao para inicializar o tabuleiro do jogo da velha com espacos vazios
void inicializar_tabuleiro()
{
    int i, j;
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Funcao para colocar um simbolo (X ou O) em uma posicao especificada
int colocar_simbolo(int linha, int coluna, char simbolo)
{
    if (linha < 0 || linha >= LINHAS || coluna < 0 || coluna >= COLUNAS)
    {
        printf("Posicao invalida!\n");
        return 0;
    }
    if (tabuleiro[linha][coluna] == ' ' )
    {
       
        tabuleiro[linha][coluna] = simbolo;
        return 1;
    }

    if (tabuleiro[linha][coluna] != ' ')
    {
        printf("Posicao ja ocupada!\n");
        return 0;
    }

    tabuleiro[linha][coluna] = simbolo;
    return 1;
}

// Funcao para verificar se algum jogador ganhou
char verificar_vencedor()
{
    int i, j;
    // Verificar linhas e colunas
    for (i = 0; i < LINHAS; i++)
    {
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
int verificar_empate()
{
    int i, j;
    // Verificar se todas as colulas estao preenchidas
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            if (tabuleiro[i][j] == ' ')
                return 0; // Ainda ha colunas vazias, o jogo nao estao empatado
        }
    }
    // Se todas as colunas estiverem preenchidas e nao houver vencedor, ha um empate
    return 1;
}

void definir_linha_coluna(InputMouse *data)
{
    int deslocamento_x = 0;
    int deslocamento_y = 0;

    if ((dx != dxAnterior) || (dy != dyAnterior))
    {
        dxAnterior = dx;
        dyAnterior = dy;

        if (abs(dx) > abs(dy))
        {
            if (dx > 0 && data->coluna < 3)
            {
                deslocamento_x = 1;
            }
            else if (dx < 0 && data->coluna > 1)
            {
                deslocamento_x = -1;
            }

            sleep(0.5);
        }
        else
        {
            if (dy > 0 && data->linha > 1)
            {
                deslocamento_y = -1;
            }
            else if (dy < 0 && data->linha < 3)
            {
                deslocamento_y = 1;
            }

            sleep(0.5);
        }

        data->linha += deslocamento_y;
        data->coluna += deslocamento_x;
    }
}

// Funcao para perguntar ao jogador em qual posicao ele deseja colocar seu simbolo
void escolher_quadrante(InputMouse *data)
{
    int jogada_feita = 0; // Variável para controlar se o jogador fez uma jogada
    int confirmar_jogada = 0;

    if (botaoEsquerdo != botaoEsquerdoAnterior)
    {

        if (botaoEsquerdo & 0x01)
        {
            confirmar_jogada = 1;
        }

        botaoEsquerdoAnterior = botaoEsquerdo;

        if (confirmar_jogada)
        {
            if (colocar_simbolo(data->linha - 1, data->coluna - 1, jogador))
            {
                jogada_feita = 1; // Define que o jogador fez uma jogada válida

                // Alternar entre X e O
                if (jogador == 'X')
                {
                    jogador = 'O';
                }
                else
                {
                    jogador = 'X';
                }
            }
            confirmar_jogada = 0;
        }
    }
}

int main()
{
    pthread_t threadMouse;
   
    InputMouse inputMouse = {2, 2, 0};

    if (pthread_create(&threadMouse, NULL, monitorarMouse, NULL))
    {
        fprintf(stderr, "Erro ao criar a thread do mouse\n");
        return 1;
    }

    while (1)
    {
        if (onMenu = 1)
        {
            printf("###### Bem vindo! ######\n");
            printf("Pressione o botao do meio para jogar\n");

            inicializar_tabuleiro();
            jogador = 'X';

            // Inicia o jogo quando aperta o botão do meio
            while (1) {
                if (botaoMeio != botaoMeioAnterior)
                {   
                    if (botaoMeio & 0x04)
                    {
                        onMenu = 0;
                        break;
                    }

                    botaoMeioAnterior = botaoMeio;
                }
            }
        }

        if (onMenu == 0)
        {
            int cont = 0;
            onMenu = 1;

            // Loop principal do jogo
            while (1)
            {      
                // Captura o input para pausa (botão direito)
                if (botaoDireito != botaoDireitoAnterior)
                {   
                    if (botaoDireito & 0x02)
                    {
                        if (pauseGame == 1)
                        {   
                            pauseGame = 0;
                        }

                        else if (pauseGame == 0)
                        {   
                            pauseGame = 1;
                        }
                    }

                    botaoDireitoAnterior = botaoDireito;
                }

                // Se não tiver pausado:
                if (pauseGame == 0)
                {
                    cont = 0;
                    definir_linha_coluna(&inputMouse);
                    escolher_quadrante(&inputMouse);

                    char vencedor = verificar_vencedor();
                    if (vencedor != ' ')
                    {
                        system("clear");
                        printf("Parabens! O jogador %c venceu!\n", vencedor);
                        break;
                    }
                    if (verificar_empate())
                    {
                        system("clear");
                        printf("Empate!\n");
                        break;
                    }

                    if (playing)
                    {
                        if ((dx != dxAnterior) || (dy != dyAnterior) || (botaoEsquerdo != botaoEsquerdoAnterior))
                        {
                            system("clear");
                            printf("Vez de %c - ", jogador);
                            printf("Linha X Coluna: %i -- %i\n", inputMouse.linha, inputMouse.coluna);

                            int positionColuna = inputMouse.coluna;
                            int positionLinha = inputMouse.linha;

                            // Copia o tabuleiro original para printar
                            for (int i = 0; i < LINHAS; i++) {
                                for (int j = 0; j < COLUNAS; j++) {
                                    copia[i][j] = tabuleiro[i][j];
                                }
                            }

                            // Coloca o *
                            if ((copia[positionLinha - 1][positionColuna - 1]) == ' ')
                            {
                                copia[positionLinha - 1][positionColuna - 1] = '*';
                            }

                            // Printa o tabuleiro
                            int i, j;
                            for (i = 0; i < LINHAS; i++)
                            {
                                for (j = 0; j < COLUNAS; j++)
                                {
                                    if (i == positionLinha - 1 && j == positionColuna - 1)
                                    {
                                        
                                        printf(" \033[0;31m%c\033[0m ", copia[i][j]);
                                    }
                                    else
                                    {
                                        printf(" %c ", copia[i][j]);
                                    }
                                    
                                    if (j < COLUNAS - 1)
                                        printf("|");
                                }
                                printf("\n");
                                if (i < LINHAS - 1)
                                    printf("---|---|---\n");
                            }
                            printf("\n");

                            // Retira o *
                            if ((copia[positionLinha - 1][positionColuna - 1]) == '*')
                            {
                                copia[positionLinha - 1][positionColuna - 1] = ' ';
                            }
                        }

                    
                    }
                }

                // Se tiver pausado:
                else
                {

                    if (cont == 0)
                    {
                        printf("\n\nJogo pausado!\nPressione o botão direito do mouse para retornar!!");
                        printf("\nPressione o botão direito do mouse para retornar!!");
                        cont = 1;
                    }
                }
            }
        }
    }

    pthread_join(threadMouse, NULL);

    return 0;
}
