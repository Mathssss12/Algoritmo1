/*
 * ==========================================================================
 * Archivo: funcion.h
 * Proyecto: Planificacion - Algoritmo SJF (No Expropiativo)
 * Descripcion: Define las estructuras y metodos para procesar siempre la
 * tarea mas corta disponible en el sistema.
 * ==========================================================================
 */

#ifndef FUNCION_H
#define FUNCION_H

#include <stdio.h>
#include <string.h>

#define MAX_PROCESOS 10

typedef struct {
    char nombre[5];
    int  tiempoLlegada;
    int  duracion;
    int  tiempoInicio;
    int  tiempoFin;
    int  tiempoEspera;
    int  tiempoRetorno;
    int  ejecutado;     /* Bandera de estado*/
} Proceso;

void pedirDatos(Proceso procesos[], int *cantidad);
int buscarMasCorto(Proceso procesos[], int cantidad, int reloj);
void calcularTiempos(Proceso procesos[], int cantidad);
void mostrarTabla(Proceso procesos[], int cantidad);
void mostrarPromedios(Proceso procesos[], int cantidad);

#endif