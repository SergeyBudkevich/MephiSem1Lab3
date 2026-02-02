
#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ERR_OK,
    ERR_INPUT,
    ERR_MEMORY,
    ERR_EOF,
    ERR_INDEX, 
    ERR_EMPTY
} err;

err init_arr(int **, int *, int *, int, err); 
err member_app(int **, int *, int *, int, err, int, err);
err member_del(int **, int *, int *, int, err);
err uniq_elem(int **, int *, int *);

#endif

