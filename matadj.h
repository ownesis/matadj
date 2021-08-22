#ifndef _MATADJ_H_
#define _MATADJ_H_

#include <stdint.h>
#include <stddef.h>

#define MA_SET(m, r, c, v) \
    m->matrice[r][c] = v

#define MA_GET(m, r, c) \
    m->matrice[r][c]

#define MA_NE_SET(m, r, c, v) \
    *(m->matrice+(m->len*r+c)) = v

#define MA_NE_GET(m, r, c) \
    *(m->matrice+(m->len*r+c))

#define MA_GET_LEN(m) \
    m->len

typedef int **matrice_t;
typedef int *matrice_ne_t;
typedef void (*callback_t)(uint32_t col, int value, void *userdata);

struct Matrice_ne {
    matrice_ne_t matrice;
    size_t len;
};
typedef struct Matrice_ne matrice_ne_ctx_t;

struct Matrice {
    int *(*matrice);
    size_t len;
};
typedef struct Matrice matrice_ctx_t;


matrice_ctx_t *ma_init(void);
matrice_ne_ctx_t *ma_ne_init(void);
void ma_destroy(matrice_ctx_t *matrice);
void ma_ne_destroy(matrice_ne_ctx_t *matrice);
_Bool ma_create_matrice(matrice_ctx_t *matrice, size_t size, int default_value);
_Bool ma_ne_create_matrice(matrice_ne_ctx_t *matrice, size_t size, int default_value);
_Bool ma_foreach(matrice_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata);
_Bool ma_ne_foreach(matrice_ne_ctx_t *matrice, uint32_t row, callback_t cb, void *userdata);
void ma_print_matrice(matrice_ctx_t *matrice);
void ma_ne_print_matrice(matrice_ne_ctx_t *matrice);
_Bool ma_new_entry(matrice_ctx_t *matrice, int default_value);
matrice_t ma_get_matrice(matrice_ctx_t *matrice);

#endif /* _MATADJ_H_ */
