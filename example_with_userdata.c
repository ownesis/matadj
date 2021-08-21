/*  Usage: 
 *  $ make
 *  $ gcc example.c matadj.o
 * */

#include <stdio.h>
#include <stdlib.h>
#include "matadj.h"

struct Data {
    int *array;
    size_t array_size;
    size_t nb_set;
};

void cb(uint32_t col, int value, void *userdata) {
    struct Data *data = (struct Data *)userdata;
    
    data->array[col] = value;

    if (value == 1) {
        data->nb_set++;
        printf(" - column '%ld'\n", col);
    }

}

int main(int argc, char *argv[]) {
    matrice_ctx_t *matrice_ctx = ma_init();
    struct Data data = {NULL, 0, 0};
    int value;

    ma_create_matrice(matrice_ctx, 20, 0);
    printf("\n[+] Create a matrice of size: 20\n");
    
    ma_new_entry(matrice_ctx, 0);
    printf("[+] Add a new entry, the matrice is now of size: %ld\n", ma_get_len(matrice_ctx));
    
    data.array_size = ma_get_len(matrice_ctx);
    data.array = calloc(data.array_size, sizeof(int));

    if (!data.array) {
        perror("calloc");
        return -1;
    }

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
    ma_foreach(matrice_ctx, 1, cb, &data);

    printf("\n[i] copy des colonnes de la ligne 1\n");
    for (size_t i = 0; i < data.array_size; i++)
        printf(" - [%d] = '%d'\n", i, data.array[i]);

    printf("\n[i] Il y'a %d colonne mis à '1'\n", data.nb_set);

    free(data.array);

    ma_destroy(matrice_ctx);            

    return 0;
}
