// produccion.c
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
        printf("Ingrese la cantidad de productos a agregar (máximo 5): ");
        scanf("%d", &cantidad);
        if (cantidad <= 0)
            printf("La cantidad debe ser mayor a 0.\n");
        else if (cantidad > 5)
            printf("El máximo permitido es 5 productos.\n");
    } while (cantidad <= 0 || cantidad > 5);

    if (totalProductos + cantidad > MAX_PRODUCTOS) {
        printf("No hay espacio suficiente para agregar %d productos.\n", cantidad);
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        printf("\nProducto %d:\n", i + 1);

        // Nombre del producto
        do {
            printf("Nombre del producto: ");
            scanf("%s", *(productos + totalProductos));
            if (buscarProducto(*(productos + totalProductos)) != -1)
                printf("El producto ya existe. Ingrese un nombre diferente.\n");
        } while (buscarProducto(*(productos + totalProductos)) != -1);

        // Tiempo total de producción (por producto)
        do {
            printf("Cantidad de Tiempo de producción disponible (minutos): ");
            scanf("%d", tiempoDisponibleProducto + totalProductos);
            if (*(tiempoDisponibleProducto + totalProductos) <= 0)
                printf("El tiempo debe ser mayor a 0.\n");
        } while (*(tiempoDisponibleProducto + totalProductos) <= 0);

        // Recursos totales disponibles (por producto)
        do {
            printf("Cantidad total de Recursos disponibles: ");
            scanf("%d", recursosDisponibleProducto + totalProductos);
            if (*(recursosDisponibleProducto + totalProductos) <= 0)
                printf("Los recursos deben ser mayores a 0.\n");
        } while (*(recursosDisponibleProducto + totalProductos) <= 0);

        // Tiempo por unidad
        do {
            printf("Tiempo de fabricación por unidad: ");
            scanf("%d", tiempo + totalProductos);
            if (*(tiempo + totalProductos) <= 0)
                printf("El tiempo debe ser mayor a 0.\n");
        } while (*(tiempo + totalProductos) <= 0);

        // Recursos por unidad
        do {
            printf("Recursos por unidad: ");
            scanf("%d", recursos + totalProductos);
            if (*(recursos + totalProductos) <= 0)
                printf("Los recursos deben ser mayores a 0.\n");
        } while (*(recursos + totalProductos) <= 0);

        // Demanda
        do {
            printf("Cantidad demandada: ");
            scanf("%d", demanda + totalProductos);
            if (*(demanda + totalProductos) <= 0)
                printf("La demanda debe ser mayor a 0.\n");
        } while (*(demanda + totalProductos) <= 0);

        totalProductos++;
    }
}


void editarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Nombre del producto a editar: ");
    scanf("%s", nombre);

    // Buscar el producto
    int pos = buscarProducto(nombre);
    if (pos == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Edicion de datos utilizando punteros
    printf("Nuevo nombre: ");
    scanf("%s", *(productos + pos));

    do {
        printf("Nuevo tiempo: ");
        scanf("%d", (tiempo + pos));
        if (*(tiempo + pos) <= 0)
            printf("El tiempo debe ser mayor a 0.\n");
    } while (*(tiempo + pos) <= 0);

    do {
        printf("Nuevos recursos: ");
        scanf("%d", (recursos + pos));
        if (*(recursos + pos) <= 0)
            printf("Los recursos deben ser mayores a 0.\n");
    } while (*(recursos + pos) <= 0);

    do {
        printf("Nueva demanda: ");
        scanf("%d", (demanda + pos));
        if (*(demanda + pos) <= 0)
            printf("La demanda debe ser mayor a 0.\n");
    } while (*(demanda + pos) <= 0);

    printf("Producto editado correctamente.\n");
    printf("Nuevo tiempo: %d, Nuevos recursos: %d, Nueva demanda: %d\n", *(tiempo + pos), *(recursos + pos), *(demanda + pos));
}


void eliminarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Nombre del producto a eliminar: ");
    scanf("%s", nombre);

    // Buscar el producto
    int pos = buscarProducto(nombre);
    if (pos == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Desplazamiento de los elementos utilizando punteros
    for (int i = pos; i < totalProductos - 1; i++) {
        strcpy(*(productos + i), *(productos + i + 1));
        *(tiempo + i) = *(tiempo + i + 1);
        *(recursos + i) = *(recursos + i + 1);
        *(demanda + i) = *(demanda + i + 1);
    }
    totalProductos--;

    printf("Producto eliminado correctamente.\n");
}

void calcularTotales(int tiempoDisponible, int recursosDisponibles)
{
    int tiempoTotal = 0, recursosTotales = 0;

    // Preguntar por el producto a mostrar
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a mostrar: ");
    scanf("%s", nombre);

    int pos = buscarProducto(nombre);
    if (pos == -1)
    {
        printf("Producto no encontrado.\n");
        return;
    }

    // Mostrar en formato tabla
    printf("-----------------------------------------------------\n");
    printf("| Nombre             | Tiempo (min) | Recursos | Demanda |");
    printf("-----------------------------------------------------\n");
    printf("| %-18s | %-12d | %-8d | %-7d |", *(productos + pos), *(tiempo + pos), *(recursos + pos), *(demanda + pos));
    printf("-----------------------------------------------------\n");

    // Calcular los totales
    for (int i = 0; i < totalProductos; i++) {
        tiempoTotal += *(tiempo + i) * *(demanda + i);
        recursosTotales += *(recursos + i) * *(demanda + i);
    }

    printf("\nTiempo total requerido: %d\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("Se puede cumplir con la demanda.\n");
    } else {
        if (tiempoTotal > tiempoDisponible)
            printf("No se cumple por falta de tiempo (Faltan %d minutos).\n", tiempoTotal - tiempoDisponible);

        if (recursosTotales > recursosDisponibles)
            printf("No se cumple por falta de recursos (Faltan %d unidades).\n", recursosTotales - recursosDisponibles);
    }
}
