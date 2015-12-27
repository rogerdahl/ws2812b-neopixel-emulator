#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#include "Arduino.h"

void delay(int ms)
{
    usleep(ms * 1000);
}

int random(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}

uint32_t millis()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}
