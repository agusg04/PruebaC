/*
 ============================================================================
 Name        : PruebaC.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct namep {
	char name[40]; /*Nombre de un producto*/
};

struct mat_prod {
	int nfil; /*número de productos*/
	int ncol; /*número de características*/
	int *pm; /*puntero a matriz*/
	struct namep *vname; /*puntero a vector de tipo struct namep*/
};

void Cargar_datos(char *filename, struct mat_prod *datos) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    if (fscanf(file, "%d %d", &datos->nfil, &datos->ncol) != 2) {
        printf("Error al leer el número de productos y características.\n");
        fclose(file);
        return;
    }
    printf("Número de productos: %d\n", datos->nfil);
    printf("Número de características: %d\n", datos->ncol);

    datos->vname = (struct namep *)malloc(datos->nfil * sizeof(struct namep));
    if (datos->vname == NULL) {
        printf("Error al asignar memoria para los nombres de los productos.\n");
        fclose(file);
        return;
    }

    datos->pm = (int *)malloc(datos->nfil * datos->ncol * sizeof(int));
    if (datos->pm == NULL) {
        printf("Error al asignar memoria para la matriz de características.\n");
        free(datos->vname);
        fclose(file);
        return;
    }

    for (int i = 0; i < datos->nfil; i++) {
        if (fscanf(file, "%s", datos->vname[i].name) != 1) {
            printf("Error al leer el nombre del producto %d.\n", i+1);
            free(datos->pm);
            free(datos->vname);
            fclose(file);
            return;
        }
        printf("Nombre del producto %d: %s\n", i+1, datos->vname[i].name);

        for (int j = 0; j < datos->ncol; j++) {
            if (fscanf(file, "%d", &datos->pm[i * datos->ncol + j]) != 1) {
                printf("Error al leer las características del producto %d.\n", i+1);
                free(datos->pm);
                free(datos->vname);
                fclose(file);
                return;
            }
            printf("Característica %d del producto %d: %d\n", j+1, i+1, datos->pm[i * datos->ncol + j]);
        }
    }

    fclose(file);
}

int main() {
    struct mat_prod datos;
    char filename[] = "datos.txt";
    Cargar_datos(filename, &datos);
    return 0;
}
// namespace *))


