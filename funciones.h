// funciones.h
#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 30

char productos[MAX_PRODUCTOS][MAX_NOMBRE];
int tiempo[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int demanda[MAX_PRODUCTOS];
int totalProductos;
int opcion;
int tiempoDisponibleProducto[MAX_PRODUCTOS];
int recursosDisponibleProducto[MAX_PRODUCTOS];

int buscarProducto(char nombre[]);
void agregarProducto();
void editarProducto();
void eliminarProducto();
void calcularTotales();

#endif
