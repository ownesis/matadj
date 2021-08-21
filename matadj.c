#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matadj.h"

static _Bool _ma_extend(matrice_ctx_t *matrice);
static _Bool _ma_append(matrice_ctx_t *matrice);

/* add row */
static _Bool _ma_extend(matrice_ctx_t *matrice) {
    int *(*tmp) = NULL;
   
    tmp = realloc(matrice->matrice, (matrice->row+1) * sizeof(int *));
    if (!tmp)
        return 0;

    /* allocate new row */
    tmp[matrice->row] = calloc(matrice->col, sizeof(int));

    if (!*tmp)
        return 0;

    matrice->row++;
    matrice->matrice = tmp;

    return 1;
}

/* add column for each row */
static _Bool _ma_append(matrice_ctx_t *matrice) {
    int *tmp = NULL;

    for (int i = 0; i < matrice->row; i++) {
        tmp = realloc(matrice->matrice[i], (matrice->col+1) * sizeof(int));
        if (!tmp)
            return 0;
        
        matrice->matrice[i] = tmp;
    }

    matrice->col++;

    return 1;
}

matrice_ctx_t *ma_init(void) {
    matrice_ctx_t *matrice = malloc(sizeof(matrice_ctx_t));
    
    memset(matrice, 0, sizeof(matrice_ctx_t));
    matrice->matrice = malloc(1);

    return matrice;
}

void ma_destroy(matrice_ctx_t *matrice) {
    for (int i = 0; i < matrice->row; i++)
        free(matrice->matrice[i]);

    free(matrice->matrice);
    free(matrice);
}

_Bool ma_new_entry(matrice_ctx_t *matrice, int default_value) {
    int *tmp = NULL;
   
    if (!_ma_extend(matrice))
        return 0;

    if (!_ma_append(matrice))
        return 0;

    /* fill all new column */
    for (uint32_t i = 0; i < matrice->row; i++)
        matrice->matrice[i][matrice->col-1] = default_value;

    /* fill new row */
    for (uint32_t i = 0; i < matrice->col; i++)
        matrice->matrice[matrice->row-1][i] = default_value;

    matrice->len += 1;

    return 1;
}

void ma_print_matrice(matrice_ctx_t *matrice) {
    for (int i = 0; i < matrice->row; i++) {
        printf(" (%d)\t", i);
        for (int j = 0; j < matrice->col; j++) {
            printf("[%d]", matrice->matrice[i][j]);
        }
        printf("\n");
    }
}

matrice_t ma_get_matrice(matrice_ctx_t *matrice) {
    return matrice->matrice;
}

size_t ma_get_len(matrice_ctx_t *matrice) {
    return matrice->len;
}

_Bool ma_create_matrice(matrice_ctx_t *matrice, size_t size, int default_value) {
    for (uint32_t i = 0; i < size; i++)
        if (!ma_new_entry(matrice, default_value))
            return 0;

    for (uint32_t i = 0; i < matrice->row; i++) {
        memset(matrice->matrice[i], default_value, matrice->col*sizeof(int));
    }

}

_Bool ma_foreach(matrice_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata) {
    if (row >= matrice->row)
        return 0;
    
    for (uint32_t i = 0; i < matrice->col; i++) {
        cb(i, matrice->matrice[row][i], userdata);
    }

    return 1;
}
