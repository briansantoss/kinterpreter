#include <stdio.h>
#include <string.h>

#include "kilate/config.h"
#include "kilate/file.h"
#include "kilate/interpreter.h"
#include "kilate/lexer.h"
#include "kilate/native.h"
#include "kilate/parser.h"
#include "kilate/stringutils.h"
#include "kilate/vector.h"

int interpret(char *src)
{
        lexer_t *lexer = lexer_make(src);
        if (lexer == NULL)
                error_exit("Lexer is null.");

        lexer_tokenize(lexer);
        return 0;

        native_init();

        parser_t *parser = parser_make(lexer->tokens);
        if (parser == NULL)
                error_exit("Parser is null.");

        parser_parse_program(parser);

        interpreter_t *interpreter =
            interpreter_make(parser->nodes, native_functions);
        if (interpreter == NULL)
                error_exit("Interpreter is null.");
        interpreter_result_t result = interpreter_run(interpreter);
        parser_delete(parser);
        interpreter_delete(interpreter);
        lexer_delete(lexer);
        native_end();

        if (result.value.type == NODE_VALUE_TYPE_INT) {
                return result.value.i;
        }
        return -1;
}

int run(int argc, char *argv[])
{
        if (argc < 2) {
                printf("Invalid usage. Use '%s help' for more info.\n",
                       argv[0]);
                return false;
        }

        if (str_equals(argv[1], "help")) {
                printf("Usage:\n");
                printf("  %s run <mainfile> [-I<path>] [-l<lib>]\n", argv[0]);
                printf("Options:\n");
                printf("  -L<path>    Kilate Libraries path\n");
                printf("  -LN<path>   Kilate Native Libraries path\n");
                return 0;
        }

        if (!str_equals(argv[1], "run")) {
                printf("Unknown command: %s\n", argv[1]);
                return -1;
        }

        if (argc < 3) {
                printf("Usage: %s run <file(s)> [-I<path>] [-l<lib>]\n",
                       argv[0]);
                return -1;
        }

        

        // Config
        {
                const char *PREFIX = getenv("PREFIX");
                if (PREFIX != NULL) {
                        char path[512];
                        snprintf(path, sizeof(path), "%s/kilate/native_libs/",
                                 PREFIX);
                        char *dup = strdup(path);
                        vector_push_back(libs_native_directories, &dup);

                        memset(path, 0, sizeof(path));
                        snprintf(path, sizeof(path), "%s/kilate/libs/",
                                 PREFIX);
                        dup = strdup(path);
                        vector_push_back(libs_directories, &dup);
                }
        }

        const char *filepath = argv[2];
        for (int i = 3; i < argc; i++) {
                char *arg = argv[i];
                if (arg[0] == '-') {
                        if (strncmp(arg, "-LN", 3) == 0) {
                                char *dup = strdup(&arg[3]);
                                vector_push_back(libs_native_directories,
                                                 &dup);
                        } else if (strncmp(arg, "-L", 2) == 0) {
                                char *dup = strdup(&arg[2]);
                                vector_push_back(libs_directories, &dup);
                        } else {
                                printf("Unknown option: %s\n", arg);
                                return -1;
                        }
                }
        }

        const char *src = file_read_all(filepath);

        int res = interpret(src);
        free(src);
        return res;
}

int main(int argc, char *argv[])
{
        config_init();
        int run_res = run(argc, argv);
        config_end();
        return run_res;
}
