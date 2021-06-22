#include "mandelbrot.h"

#ifdef __linux__
#   include <time.h>
void sleepMillis(unsigned millis)
{
    struct timespec req = { millis / 1000, (millis % 1000) * 1000 };
    nanosleep(&req, 0);
}
#elif _WIN32
#   include <Windows.h>
void sleepMillis(unsigned millis)
{
    Sleep(millis);
}
#else
#   error "Unknown OS"
#endif

