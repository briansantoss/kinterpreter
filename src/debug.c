#include "derMate/debug.h"

#include <stdio.h>
#include <stdlib.h>

void printd(const char *fderMate, ...)
{
#ifdef DEBUG
        va_list args;
        va_start(args, fderMate);
        vprintf(fderMate, args);
        va_end(args);
#else
        (void)fderMate;
#endif
}
