/*
 * ==========================================================================
 * Archivo: funcion.h
 * Proyecto: Planificacion de Procesos - Algoritmo FIFO (FCFS)
 * Descripcion: Define la estructura del proceso y declara las funciones
 * utilizadas para simular el algoritmo First-In, First-Out.
 * Autor: [Tu nombre]
 * Fecha: 2025
 * ==========================================================================
 */

#ifndef FUNCION_H
#define FUNCION_H

#include <stdio.h>
#include <string.h>

/* Capacidad maxima de procesos en el sistema */
#define MAX_PROCESOS 10

/*
 * Estructura: Proceso
 */
typedef struct {
    char nombre[5];         /* Identificador del proceso */
    int  tiempoLlegada;     /* Momento en que entra a la cola de listos */
    int  duracion;          /* Ráfaga de CPU requerida */
    int  tiempoInicio;      /* Momento en que el CPU comienza a procesarlo */
    int  tiempoFin;         /* Momento en que libera el CPU */
    int  tiempoEspera;      /* Tiempo total en cola  */
    int  tiempoRetorno;     /* Tiempo total en sistema  */
} Proceso;

/* Prototipos de funciones */
void pedirDatos(Proceso procesos[], int *cantidad);
void ordenarPorLlegada(Proceso procesos[], int cantidad);
void calcularTiempos(Proceso procesos[], int cantidad);
void mostrarTabla(Proceso procesos[], int cantidad);
void mostrarPromedios(Proceso procesos[], int cantidad);

#endif