#ifndef KILATE_NATIVE_H
#define KILATE_NATIVE_H

#include "kilate/environment.h"
#include "kilate/interpreter.h"
#include "kilate/stringutils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct native_fndata_t {
        interpreter_t *inter;
        node_arg_vector_t *args;
} native_fndata_t;

typedef return_node_t *(*native_fn_t)(native_fndata_t *);

#define KILATE_NATIVE_REGISTER() void KILATE_NATIVE_REGISTER()

extern node_vector_t *native_functions;

void native_init();

void native_load_extern();

void native_end();

void native_register_function_node(native_function_node_t *);

void native_register_fn(const char *, const char *, node_vector_t *, native_fn_t);

native_function_node_t *native_find_function(const char *);

void native_register_all_functions();

#ifdef __cplusplus
}
#endif

#endif
