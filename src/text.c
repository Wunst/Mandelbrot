#include "mandelbrot.h"

#include <stdio.h>

// Shameless copy from
// https://stackoverflow.com/questions/14002954
char* textLoad(const char *path)
{
    FILE *f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;

    return string;
}



void textFree(char *text)
{
    free(text);
}
