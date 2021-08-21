#ifndef _MATADJ_H_
#define _MATADJ_H_

#include <stdint.h>
#include <stddef.h>

#define MA_SET(m, r, c, v) \
    m->matrice[r][c] = v

#define MA_GET(m, r, c) \
    m->matrice[r][c]

typedef int **matrice_t;
typedef void (*callback_t)(uint32_t col, int value, void *userdata);

struct Matrice {
    int *(*matrice);
    size_t len;
};
typedef struct Matrice matrice_ctx_t;


matrice_ctx_t *ma_init(void);
void ma_destroy(matrice_ctx_t *matrice);
_Bool ma_new_entry(matrice_ctx_t *matrice, int default_value);
void ma_print_matrice(matrice_ctx_t *matrice);
matrice_t ma_get_matrice(matrice_ctx_t *matrice);
size_t ma_get_len(matrice_ctx_t *matrice);
_Bool ma_create_matrice(matrice_ctx_t *matrice, size_t size, int default_value);
_Bool ma_foreach(matrice_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata);

#endif /* _MATADJ_H_ */
