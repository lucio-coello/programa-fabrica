//main.c
#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion; 

    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Verificar produccion\n");
        printf("5. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Por favor ingrese un numero.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                calcularTotales(); 
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

        while (getchar() != '\n');

    } while (opcion != 5);

    return 0;
}

//fin del main.c
