#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matadj.h"

static _Bool _ma_extend(matrice_ctx_t *matrice);
static _Bool _ma_append(matrice_ctx_t *matrice);

_Bool ma_ne_create_matrice(matrice_ne_ctx_t *matrice, size_t size, int default_value) {
    matrice->matrice = calloc(size*size, sizeof(int)); 
    if (!matrice->matrice)
        return 0;

    if (!memset(matrice->matrice, default_value, size*sizeof(int)))
        return 0;

    matrice->len = size;
    
    return 1;
}

matrice_ne_ctx_t *ma_ne_init(void) {
    matrice_ne_ctx_t *matrice = malloc(sizeof(matrice_ne_ctx_t));
    
    if(!memset(matrice, 0, sizeof(matrice_ne_ctx_t)))
        return NULL;
    
    matrice->matrice = NULL;

    return matrice;
}

void ma_ne_destroy(matrice_ne_ctx_t *matrice) {
    free(matrice->matrice);
    free(matrice);
}

void ma_ne_print_matrice(matrice_ne_ctx_t *matrice) {
    for (size_t i = 0; i < matrice->len; i++) {
        printf(" (%ld)\t", i);
        for (size_t j = 0; j < matrice->len; j++) {
            printf("[%d]", MA_NE_GET(matrice, i, j));
        }
        printf("\n");
    }
}

_Bool ma_ne_foreach(matrice_ne_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata) {
    if (row >= matrice->len)
        return 0;
    
    for (size_t i = 0; i < matrice->len; i++) {
        cb(i, MA_NE_GET(matrice, row, i), userdata);
    }

    return 1;
}


/* add row */
static _Bool _ma_extend(matrice_ctx_t *matrice) {
    int *(*tmp) = NULL;
   
    tmp = realloc(matrice->matrice, (matrice->len+1) * sizeof(int *));
    if (!tmp)
        return 0;

    /* allocate new row */
    tmp[matrice->len] = calloc(matrice->len, sizeof(int));

    if (!*tmp)
        return 0;

    matrice->matrice = tmp;

    return 1;
}

/* add column for each row */
static _Bool _ma_append(matrice_ctx_t *matrice) {
    int *tmp = NULL;

    for (size_t i = 0; i < matrice->len+1; i++) {
        tmp = realloc(matrice->matrice[i], (matrice->len+1) * sizeof(int));
        if (!tmp)
            return 0;
        
        matrice->matrice[i] = tmp;
    }

    return 1;
}

matrice_ctx_t *ma_init(void) {
    matrice_ctx_t *matrice = malloc(sizeof(matrice_ctx_t));
    
    if (!memset(matrice, 0, sizeof(matrice_ctx_t)))
        return NULL;

    matrice->matrice = malloc(1);

    return matrice;
}

void ma_destroy(matrice_ctx_t *matrice) {
    for (size_t i = 0; i < matrice->len; i++)
        free(matrice->matrice[i]);

    free(matrice->matrice);
    free(matrice);
}

_Bool ma_new_entry(matrice_ctx_t *matrice, int default_value) {
    if (!_ma_extend(matrice))
        return 0;
    
    if (!_ma_append(matrice))
        return 0;

    /* fill all new column */
    for (uint32_t i = 0; i < matrice->len+1; i++)
        matrice->matrice[i][matrice->len] = default_value;

    /* fill new row */
    for (uint32_t i = 0; i < matrice->len+1; i++)
        matrice->matrice[matrice->len][i] = default_value;

    matrice->len += 1;

    return 1;
}

void ma_print_matrice(matrice_ctx_t *matrice) {
    for (size_t i = 0; i < matrice->len; i++) {
        printf(" (%ld)\t", i);
        for (size_t j = 0; j < matrice->len; j++) {
            printf("[%d]", matrice->matrice[i][j]);
        }
        printf("\n");
    }
}

matrice_t ma_get_matrice(matrice_ctx_t *matrice) {
    return matrice->matrice;
}

_Bool ma_create_matrice(matrice_ctx_t *matrice, size_t size, int default_value) {
    for (size_t i = 0; i < size; i++)
        if (!ma_new_entry(matrice, default_value))
            return 0;

    for (size_t i = 0; i < matrice->len; i++) {
        if (!memset(matrice->matrice[i], default_value, matrice->len*sizeof(int)))
            return 0;
    }

    return 1;
}

_Bool ma_foreach(matrice_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata) {
    if (row >= matrice->len)
        return 0;
    
    for (size_t i = 0; i < matrice->len; i++) {
        cb(i, matrice->matrice[row][i], userdata);
    }

    return 1;
}
