# Matadj
Matadj (**Mat**rice **Adj**acente) est une bibliothèque de fonction qui permet de créer et utiliser une matrice d'adjacence en C

# Usage
## Compilation
```sh
make
gcc example.c matadj.o -o example
```

# Documentation
### Initialiser le context de la matrice
**Retour**
> Retourne un pointer vers `matrice_ctx_t`
```c
matrice_ctx_t *matrice_ctx = ma_init();
```

### Supprimer le context de la matrie
**Arguments**
> matrice: `matrice_ctx_t`
```c
ma_destroy(matrice_ctx);
```

### Crééer une matrice d'une taille donnée
**Arguments**
> matrice: `matrice\_ctx\_t`
> size: `size_t`
> default\_value: `int`

**Retour**
> Retourn `1` en cas du succès ou `0` en cas d'erreur.
```c
/* Crééer une matrice de 10\*10 tout initialisé à `0' */
_Bool ret = ma_create_matrice(marice_ctx, 10, 0);
```

### Ajouter une nouvelle entrée dans la matrice
**Arguments**
> matrice: `matrice_ctx_t`
> default\_value: `int`

**Retour**
> Retourne `1` en cas de succès ou `0` en cas d'erreur
```c
_Bool ret = ma_new_entry(matrice_ctx, 0);
```

### Récupérer la taille de la matrice (ex: 10 si matrice de 10\*10)
**Arguments**
> matrice: `matrice_ctx_t`

**Retour**
> La taille de la matrice
```c
size_t matrice_len = ma_get_len(matrice_ctx);
```

### Récupérer la matrice
Ne pas oublier de récupérer la matrice après chaque appel de ma\_new\_entry();
**Arguments**
> matrice: `matrice_ctx_t`

**Retourne**
> Retourne la matrice de type `matrice_t` alias `int **`
```c
matrice_t matrice = ma_get_matrice(matrice_ctx);
```

### Parcourir les valeurs de chaque colonne d'une ligne donnée.
**Arguments**
> matrice: `matrice_ctx_t`
> row: `uint32_t`
> callback: `callback_t` alias `void (*)(uint32_t col, int value, void *userdata)`
> userdata: `void *`

**Retour**
> Retourne `1` en cas de succès ou `0` en cas d'erreur.
```c
void my_callback(uint32_t col, int value, void *userdata) {
    printf("[%ld] = '%d'\n", col, value);
}

/* Parcour toutes les colonnes de la ligne `1' */
_Bool ret = ma_foreach(matrice_ctx, 1, my_callback, NULL);
```

### Afficher la matrice
**Arguments**
> matrice: `matrice_ctx_t`
```c
ma_print_matrice(matrice_ctx);
```

### Assigner une valeur dans la matrice
Avec `ma_get_matrice()`
```c
matrice_t matrice = ma_get_matrice(matrice_ctx);
matrice[4][2] = 42;
```
Avec la macro `MA_SET()`
**Arguments**
> m: `matrice_ctx_t`
> r: row `uint32_t`
> c: column `uint32_t`
> v: value `int`
```c
MA_SET(matrice_ctx, 4, 2, 42);
```

### Récupérer une valeur dans la matrice
Avec `ma_get_matrice()`
```c
matrice_t matrice = ma_get_matrice(matrice_ctx);
int val = matrice[4][2];
```
Avec la macro `MA_GET()`
**Arguments**
> m: `matrice_ctx_t`
> r: row `uint32_t`
> c: column `uint32_t`

**Retour**
> Retourne la valeur à l'index indiqué
```c
int val = MA_SET(matrice_ctx, 4, 2);
```
