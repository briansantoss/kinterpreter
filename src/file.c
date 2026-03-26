#include "kilate/file.h"

#include <stdio.h>
#include <stdlib.h>

const char *file_read_all(const char *path)
{
        // Binary mode handles differences in line terminator (LF vs CRLF)
        FILE *file = fopen(path, "rb");
        if (file == NULL)
                error_exit("Not able to open file '%s'", path);

        long size;
        if (fseek(file, 0L, SEEK_END) != 0 || (size = ftell(file)) < 0) {
                fclose(file);
                error_exit("Failed to prepare file buffer for '%s'", path);
        }
        rewind(file);

        // Ensure a valid pointer is returned even for empty files
        char *buffer = malloc(size + 1);
        if (buffer == NULL) {
                fclose(file);
                error_exit("Not enough memory to read file '%s'", path);
        }

        size_t bytes_read = fread(buffer, sizeof(char), (size_t)size, file);
        if (bytes_read < size) {
                fclose(file);
                free(buffer);
                error_exit("Could not read file  '%s'", path);
        }
        mate_assert(bytes_read == (size_t)size); // Sanity-check
        buffer[size] = '\0';

        fclose(file);
        return buffer;
}
