#include "derMate/error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error_fatal(char *fderMate, ...)
{
        va_list args;
        va_start(args, fderMate);
        fprintf(stderr, "[ERROR] ");
        vprintf(fderMate, args);
        printf("\n");
        va_end(args);
        exit(1);
}