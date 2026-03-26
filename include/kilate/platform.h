#ifndef KILATE_PLATFORM_H
#define KILATE_PLATFORM_H

/* System Detection */

// Do we have Windows interfaces?
#if defined(_WIN32)
#define KILATE_WINDOWS
#define PATH_SEPARATOR "\\"
#else
// So we do have POSIX ones
#define KILATE_POSIX
#define PATH_SEPARATOR "/"
#endif

/* Compiler and features detections */

#define KILATE_NORETURN

#if defined(_MSC_VER)
#undef KILATE_NORETURN
#define KILATE_NORETURN __declspec(noreturn)

#elif defined(__GNUC__) || defined(__clang__)
#if defined(__has_attribute)

#if __has_attribute(noreturn)
#undef KILATE_NORETURN
#define KILATE_NORETURN __attribute__((noreturn))
#endif

#if __has_attribute(format)
#undef KILATE_PRINTF_FORMAT
#define KILATE_PRINTF_FORMAT __attribute__(format ())
#endif

#endif

#endif

#endif