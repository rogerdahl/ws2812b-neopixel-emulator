#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#include "Arduino.h"

void delay (int ms)
{
    usleep (ms * 1000);
}

int random (int min_num, int max_num)
{
    int low_num = 0;
    int hi_num = 0;
    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    }
    else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    return (rand() % (hi_num - low_num)) + low_num;
}

uint32_t millis()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}
