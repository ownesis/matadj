/*  Usage: 
 *  $ make
 *  $ gcc example.c matadj.o
 * */

#include <stdio.h>
#include "matadj.h"

void cb(uint32_t col, int value, void *userdata) {
    if (value == 1) {
        printf(" - column '%ld'\n", col);
    }
}

int main(int argc, char *argv[]) {
    matrice_ne_ctx_t *matrice_ne_ctx = ma_ne_init();
    int value;

    ma_ne_create_matrice(matrice_ne_ctx, 20, 0);
    printf("\n[+] Create a not extendible matrice of size: %ld\n", MA_GET_LEN(matrice_ne_ctx));
    
    printf("[*] Connect row '1' with some column...\n\n");
    MA_NE_SET(matrice_ne_ctx, 1, 0, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 2, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 3, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 4, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 8, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 11, 1);
    MA_NE_SET(matrice_ne_ctx, 1, 16, 1);
    MA_NE_SET(matrice_ne_ctx, 4, 2, 42);

    value = MA_NE_GET(matrice_ne_ctx, 4, 2);
    printf("[i] '%d' inside index [4][2]\n\n", value);

    ma_ne_print_matrice(matrice_ne_ctx);

    printf("\n[i] The row 1 is connected with the following column:\n");
    ma_ne_foreach(matrice_ne_ctx, 1, cb, NULL);

    ma_ne_destroy(matrice_ne_ctx);            

    return 0;
}
