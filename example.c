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
    matrice_ctx_t *matrice_ctx = ma_init();
    int value;

    ma_create_matrice(matrice_ctx, 20, 0);
    printf("\n[+] Create a matrice of size: 20\n");
    
    ma_new_entry(matrice_ctx, 0);
    printf("[+] Add a new entry, the matrice is now of size: %ld\n", ma_get_len(matrice_ctx));

    printf("[*] Connect row '1' with some column...\n\n");
    MA_SET(matrice_ctx, 1, 0, 1);
    MA_SET(matrice_ctx, 1, 2, 1);
    MA_SET(matrice_ctx, 1, 3, 1);
    MA_SET(matrice_ctx, 1, 4, 1);
    MA_SET(matrice_ctx, 1, 8, 1);
    MA_SET(matrice_ctx, 1, 11, 1);
    MA_SET(matrice_ctx, 1, 16, 1);
    MA_SET(matrice_ctx, 4, 2, 42);

    value = MA_GET(matrice_ctx, 4, 2);
    printf("[i] '%d' inside index [4][2]\n\n", value);

    ma_print_matrice(matrice_ctx);

    printf("\n[i] The row 1 is connected with the following column:\n");
    ma_foreach(matrice_ctx, 1, cb, NULL);

    ma_destroy(matrice_ctx);            

    return 0;
}
