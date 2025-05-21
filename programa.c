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

    do {
        printf("Ingrese la cantidad de productos a agregar (maximo 5): ");
        scanf("%d", &cantidad);
        if (cantidad <= 0)
            printf("La cantidad debe ser mayor a 0.\n");
        else if (cantidad > 5)
            printf("El maximo permitido es 5 productos.\n");
    } while (cantidad <= 0 || cantidad > 5);

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
        do {
            printf("Tiempo de produccion disponible (minutos): ");
            scanf("%d", tiempoDisponibleProducto + totalProductos);
            if (*(tiempoDisponibleProducto + totalProductos) <= 0)
                printf("El tiempo debe ser mayor a 0.\n");
        } while (*(tiempoDisponibleProducto + totalProductos) <= 0);
        do {
            printf("Recursos disponibles: ");
            scanf("%d", recursosDisponibleProducto + totalProductos);
            if (*(recursosDisponibleProducto + totalProductos) <= 0)
                printf("Los recursos deben ser mayores a 0.\n");
        } while (*(recursosDisponibleProducto + totalProductos) <= 0);
        do {
            printf("Tiempo de fabricacion por unidad: ");
            scanf("%d", tiempo + totalProductos);
            if (*(tiempo + totalProductos) <= 0)
                printf("El tiempo debe ser mayor a 0.\n");
        } while (*(tiempo + totalProductos) <= 0);
        do {
            printf("Recursos por unidad: ");
            scanf("%d", recursos + totalProductos);
            if (*(recursos + totalProductos) <= 0)
                printf("Los recursos deben ser mayores a 0.\n");
        } while (*(recursos + totalProductos) <= 0);
        do {
            printf("Cantidad demandada: ");
            scanf("%d", demanda + totalProductos);
            if (*(demanda + totalProductos) <= 0)
                printf("La demanda debe ser mayor a 0.\n");
        } while (*(demanda + totalProductos) <= 0);

        printf("Producto agregado correctamente.\n");
        totalProductos++;
    }
}
void editarProducto() {
    char nombre[MAX_NOMBRE];
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

    if (buscarProducto(nuevoNombre) != -1 && strcmp(nuevoNombre, productos[pos]) != 0) {
        printf("El nombre ya existe para otro producto.\n");
        return;
    }

    strcpy(*(productos + pos), nuevoNombre);

    do {
        printf("Nuevo tiempo por unidad: ");
        scanf("%d", tiempo + pos);
        if (*(tiempo + pos) <= 0)
            printf("El tiempo debe ser mayor a 0.\n");
    } while (*(tiempo + pos) <= 0);

    do {
        printf("Nuevos recursos por unidad: ");
        scanf("%d", recursos + pos);
        if (*(recursos + pos) <= 0)
            printf("Los recursos deben ser mayores a 0.\n");
    } while (*(recursos + pos) <= 0);

    do {
        printf("Nueva demanda: ");
        scanf("%d", demanda + pos);
        if (*(demanda + pos) <= 0)
            printf("La demanda debe ser mayor a 0.\n");
    } while (*(demanda + pos) <= 0);

    do {
        printf("Nuevo tiempo disponible total: ");
        scanf("%d", tiempoDisponibleProducto + pos);
        if (*(tiempoDisponibleProducto + pos) <= 0)
            printf("El tiempo debe ser mayor a 0.\n");
    } while (*(tiempoDisponibleProducto + pos) <= 0);

    do {
        printf("Nuevos recursos disponibles totales: ");
        scanf("%d", recursosDisponibleProducto + pos);
        if (*(recursosDisponibleProducto + pos) <= 0)
            printf("Los recursos deben ser mayores a 0.\n");
    } while (*(recursosDisponibleProducto + pos) <= 0);

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
