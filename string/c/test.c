#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char * p = (char *)malloc(sizeof(char) * 4);
    memset(p, 1, 4);
    char p2;
    p = (char *)realloc(&p2, sizeof(char) * 2);
    p[3] = 0;

    return 0;
}
