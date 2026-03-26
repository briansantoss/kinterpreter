#include "kilate/base.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void error_exit(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
        va_end(args);
        exit(EXIT_FAILURE);
}