#include <stdio.h>
#include <unistd.h>
#include <intelfpgaup/LEDR.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define LEDR_H

int main(void)
{
    LEDR_open();
    for (int i = 0; i <= 9; i++)
    {
        LEDR_set(1 << i);
        sleep(1);
    };

    for (int i = 9; i >= 1; i--)
    {
        LEDR_set(1 << i);
        sleep(1);
    };

    LEDR_set(0b     );
    sleep(1);
    LEDR_set(0b0000000000);

    LEDR_close();
    return 0;
}
