#ifndef KILATE_BASE_H
#define KILATE_BASE_H

#include <stdio.h>

void error_exit(const char *fmt, ...);

#define mate_unreachable()                                                    \
        do {                                                                  \
                error_exit("[%s:%d] Unreachable code reached: %s", __FILE__,  \
                           __LINE__);                                         \
        } while (0)

#ifdef NDEBUG
#define mate_assert(cond)                                                     \
        do {                                                                  \
        } while (0)
#define mate_debug_log(fmt, ...)                                              \
        do {                                                                  \
        } while (0)
#else
#define mate_assert(cond)                                                     \
        do {                                                                  \
                if (!(cond))                                                  \
                        error_exit("[%s:%d] Assert violated: %s", __FILE__,   \
                                   __LINE__, #cond);                          \
        } while (0)

#define mate_debug_log(fmt, ...)                                              \
        do {                                                                  \
                printf("[DEBUG: %s:%d]: " fmt, __FILE__, __LINE__,            \
                       ##__VA_ARGS__);                                        \
        } while (0)
#endif

#endif