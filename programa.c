//programa.c
#include <stdio.h>
#include <string.h>
#include "funciones.h"

 
int buscarProducto(char nombre[]) {
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(*(productos + i), nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void agregarProducto() {
    int cantidad;
    int valido;

    do {
        printf("Ingrese la cantidad de productos a agregar (maximo 5): ");
        if (scanf("%d", &cantidad) == 1 && cantidad > 0 && cantidad <= 5) {
            break;
        } else {
            printf("La cantidad debe ser un numero entre 1 y 5.\n");
            while (getchar() != '\n');
        }
    } while (1);

    if (totalProductos + cantidad > MAX_PRODUCTOS) {
        printf("No hay espacio suficiente para agregar %d productos.\n", cantidad);
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nProducto %d:\n", i + 1);
        do {
            printf("Nombre del producto: ");
            scanf("%s", *(productos + totalProductos));
            if (buscarProducto(*(productos + totalProductos)) != -1)
                printf("El producto ya existe. Ingrese un nombre diferente.\n");
        } while (buscarProducto(*(productos + totalProductos)) != -1);
        valido = 0;
        while (!valido) {
            printf("Tiempo de produccion disponible (minutos): ");
            if (scanf("%d", tiempoDisponibleProducto + totalProductos) == 1 && *(tiempoDisponibleProducto + totalProductos) > 0) {
                valido = 1;
            } else {
                printf("El tiempo debe ser mayor a 0 y valido.\n");
                while (getchar() != '\n');
            }
        }

        valido = 0;
        while (!valido) {
            printf("Recursos disponibles: ");
            if (scanf("%d", recursosDisponibleProducto + totalProductos) == 1 && *(recursosDisponibleProducto + totalProductos) > 0) {
                valido = 1;
            } else {
                printf("Los recursos deben ser mayores a 0 y validos.\n");
                while (getchar() != '\n');
            }
        }

        valido = 0;
        while (!valido) {
            printf("Tiempo de fabricacion por unidad: ");
            if (scanf("%d", tiempo + totalProductos) == 1 && *(tiempo + totalProductos) > 0) {
                valido = 1;
            } else {
                printf("El tiempo debe ser mayor a 0 y valido.\n");
                while (getchar() != '\n');
            }
        }

        valido = 0;
        while (!valido) {
            printf("Recursos por unidad: ");
            if (scanf("%d", recursos + totalProductos) == 1 && *(recursos + totalProductos) > 0) {
                valido = 1;
            } else {
                printf("Los recursos deben ser mayores a 0 y válidos.\n");
                while (getchar() != '\n');
            }
        }

        
        valido = 0;
        while (!valido) {
            printf("Cantidad demandada: ");
            if (scanf("%d", demanda + totalProductos) == 1 && *(demanda + totalProductos) > 0) {
                valido = 1;
            } else {
                printf("La demanda debe ser mayor a 0 y valida.\n");
                while (getchar() != '\n');
            }
        }

        printf("Producto agregado correctamente.\n");
        totalProductos++;
    }
}

void editarProducto() {
    char nombre[MAX_NOMBRE];
    int valido;

    printf("Nombre del producto a editar: ");
    scanf("%s", nombre);

    int pos = buscarProducto(nombre);
    if (pos == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    char nuevoNombre[MAX_NOMBRE];
    printf("Nuevo nombre: ");
    scanf("%s", nuevoNombre);

    if (buscarProducto(nuevoNombre) != -1 && strcmp(nuevoNombre, *(productos + pos)) != 0) {
        printf("El nombre ya existe para otro producto.\n");
        return;
    }

    strcpy(*(productos + pos), nuevoNombre);
    valido = 0;
    while (!valido) {
        printf("Nuevo tiempo por unidad: ");
        if (scanf("%d", tiempo + pos) == 1 && *(tiempo + pos) > 0) {
            valido = 1;
        } else {
            printf("El tiempo debe ser mayor a 0 y valido.\n");
            while (getchar() != '\n');
        }
    }
    valido = 0;
    while (!valido) {
        printf("Nuevos recursos por unidad: ");
        if (scanf("%d", recursos + pos) == 1 && *(recursos + pos) > 0) {
            valido = 1;
        } else {
            printf("Los recursos deben ser mayores a 0 y validos.\n");
            while (getchar() != '\n');
        }
    }
    valido = 0;
    while (!valido) {
        printf("Nueva demanda: ");
        if (scanf("%d", demanda + pos) == 1 && *(demanda + pos) > 0) {
            valido = 1;
        } else {
            printf("La demanda debe ser mayor a 0 y valida.\n");
            while (getchar() != '\n');
        }
    }
    valido = 0;
    while (!valido) {
        printf("Nuevo tiempo disponible total: ");
        if (scanf("%d", tiempoDisponibleProducto + pos) == 1 && *(tiempoDisponibleProducto + pos) > 0) {
            valido = 1;
        } else {
            printf("El tiempo debe ser mayor a 0 y valido.\n");
            while (getchar() != '\n');
        }
    }
    valido = 0;
    while (!valido) {
        printf("Nuevos recursos disponibles totales: ");
        if (scanf("%d", recursosDisponibleProducto + pos) == 1 && *(recursosDisponibleProducto + pos) > 0) {
            valido = 1;
        } else {
            printf("Los recursos deben ser mayores a 0 y validos.\n");
            while (getchar() != '\n');
        }
    }

    printf("Producto editado correctamente.\n");
}


void eliminarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Nombre del producto a eliminar: ");
    scanf("%s", nombre);

    int pos = buscarProducto(nombre);
    if (pos == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = pos; i < totalProductos - 1; i++) {
        strcpy(*(productos + i), *(productos + i + 1));
        *(tiempo + i) = *(tiempo + i + 1);
        *(recursos + i) = *(recursos + i + 1);
        *(demanda + i) = *(demanda + i + 1);
        *(tiempoDisponibleProducto + i) = *(tiempoDisponibleProducto + i + 1);
        *(recursosDisponibleProducto + i) = *(recursosDisponibleProducto + i + 1);
    }

    totalProductos--;
    printf("Producto eliminado correctamente.\n");
}

void calcularTotales() {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a mostrar: ");
    scanf("%s", nombre);

    int pos = buscarProducto(nombre);
    if (pos == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    int tiempoTotal = *(tiempo + pos) * *(demanda + pos);
    int recursosTotales = *(recursos + pos) * *(demanda + pos);

    printf("\n--- Informacion del Producto ---\n");
    printf("Nombre: %s\n", *(productos + pos));
    printf("Tiempo por unidad: %d minutos\n", *(tiempo + pos));
    printf("Recursos por unidad: %d\n", *(recursos + pos));
    printf("Demanda: %d unidades\n", *(demanda + pos));
    printf("Tiempo total requerido: %d minutos\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);
    printf("Tiempo disponible: %d minutos\n", *(tiempoDisponibleProducto + pos));
    printf("Recursos disponibles: %d\n", *(recursosDisponibleProducto + pos));

    if (tiempoTotal <= *(tiempoDisponibleProducto + pos) && recursosTotales <= *(recursosDisponibleProducto + pos)) {
        printf("Se puede cumplir con la demanda.\n");
    } else {
        if (tiempoTotal > *(tiempoDisponibleProducto + pos))
            printf("No se cumple por falta de tiempo (Faltan %d minutos).\n", tiempoTotal - *(tiempoDisponibleProducto + pos));
        if (recursosTotales > *(recursosDisponibleProducto + pos))
            printf("No se cumple por falta de recursos (Faltan %d unidades).\n", recursosTotales - *(recursosDisponibleProducto + pos));
    }
}
// fin del programa.c
