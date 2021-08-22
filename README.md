# Matadj
Matadj (**Mat**rice **Adj**acente) est une bibliothèque de fonction qui permet de créer et utiliser une matrice d'adjacence en C

# Usage
## Compilation
```sh
make
gcc example.c matadj.o -o example
```

# Documentation
## Matrice extensible
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
> matrice: `matrice_ctx_t`
> size: `size_t`
> default\_value: `int`

**Retour**
> Retourne `1` en cas du succès ou `0` en cas d'erreur.
```c
/* Crééer une matrice de 10*10 tout initialisé à `0' */
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
size_t matrice_len = MA_GET_LEN(matrice_ctx);
```

### Récupérer la matrice
Ne pas oublier de récupérer la matrice après chaque appel de `ma_new_entry()`;
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
l'argument `userdata` est un argument optionnel, il est utile si l'utilisateur veut faire passer un objet (structure, tableau, variable...) utile pour la fonction appelé.
Voir cet [exemple](examples/example_with_userdata.c)

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

## Matrice NON extensible
La matrice non extensible est plus rapide lors de sa generation.
Seulement 2 allocations executé contrairement à la [**Matrice extensible**](#Matrce-exensible) qui est, en notation [Big O](https://en.wikipedia.org/wiki/Big_O_notation) de `O(n²)` (n = taille de la matrice).
### Initialiser le context de la matrice
**Retour**
> Retourne un pointer vers `matrice_ne_ctx_t`
```c
matrice_ne_ctx_t *matrice_ne_ctx = ma_ne_init();
```

### Supprimer le context de la matrie
**Arguments**
> matrice: `matrice_ne_ctx_t`
```c
ma_destroy(matrice_ne_ctx);
```

### Crééer une matrice d'une taille donnée
**Arguments**
> matrice: `matrice_ne_ctx_t`
> size: `size_t`
> default\_value: `int`

**Retour**
> Retourne `1` en cas du succès ou `0` en cas d'erreur.
```c
/* Crééer une matrice de 10*10 tous initialisé à `0' */
_Bool ret = ma_ne_create_matrice(marice_ne_ctx, 10, 0);
```

### Récupérer la taille de la matrice (ex: 10 si matrice de 10\*10)
Meme macro utilisé pour une matrice extensible.
**Arguments**
> matrice: `matrice_ne_ctx_t`

**Retour**
> La taille de la matrice
```c
size_t matrice_len = MA_GET_LEN(matrice_ne_ctx);
```

### Parcourir les valeurs de chaque colonne d'une ligne donnée.
**Arguments**
> matrice: `matrice_ne_ctx_t`
> row: `uint32_t`
> callback: `callback_t` alias `void (*)(uint32_t col, int value, void *userdata)`
> userdata: `void *`
l'argument `userdata` est un argument optionnel, il est utile si l'utilisateur veut faire passer un objet (structure, tableau, variable...) utile pour la fonction appelé.
Voir cet [exemple](examples/example_with_userdata.c)

**Retour**
> Retourne `1` en cas de succès ou `0` en cas d'erreur.
```c
void my_callback(uint32_t col, int value, void *userdata) {
    printf("[%ld] = '%d'\n", col, value);
}

/* Parcour toutes les colonnes de la ligne `1' */
_Bool ret = ma_foreach(matrice_ne_ctx, 1, my_callback, NULL);
```

### Afficher la matrice
**Arguments**
> matrice: `matrice_ne_ctx_t`
```c
ma_print_ne_matrice(matrice_ctx);
```

### Assigner une valeur dans la matrice
**Arguments**
> m: `matrice_ne_ctx_t`
> r: row `uint32_t`
> c: column `uint32_t`
> v: value `int`
```c
MA_NE_SET(matrice_ctx, 4, 2, 42);
```

### Récupérer une valeur dans la matrice
**Arguments**
> m: `matrice_ctx_t`
> r: row `uint32_t`
> c: column `uint32_t`

**Retour**
> Retourne la valeur à l'index indiqué
```c
int val = MA_NE_GET(matrice_ctx, 4, 2);
```
