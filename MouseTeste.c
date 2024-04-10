#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <fcntl.h>

#define LIMITE_DESLOCAMENTO 0

// Variáveis globais para armazenar movimentos e cliques do mouse
int raw_dx = 0;
int raw_dy = 0;
int dx = 0;
int dy = 0;
int botaoEsquerdo = 0;

int playing = 1;

void monitorarMouse()
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

        dx = 0;
        dy = 0;
        
        if (abs(raw_dx) >= abs(raw_dy)) {
            if (raw_dx > LIMITE_DESLOCAMENTO) 
                dx = 1;
            else if (raw_dx < -LIMITE_DESLOCAMENTO)
                dx = -1;
        } else if (abs(raw_dy) > abs(raw_dx)) {
            if (raw_dy > LIMITE_DESLOCAMENTO) 
                dy = 1;
            else if (raw_dy < -LIMITE_DESLOCAMENTO)
                dy = -1;
        }

        system('clear');
        printf("dx: %d", dx);
        // printf(" raw_dx: %d \n", raw_dx);
        printf(" dy: %d \n", dy);
        // printf(" raw_dy: %d \n", raw_dy);
    }
    close(fd);
    return NULL;
}

void main() {
    monitorarMouse();
}
