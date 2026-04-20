/*
 * ==========================================================================
 * Archivo: funcion.h
 * Proyecto: Planificacion por PRIORIDAD (No Expropiativo)
 * Descripcion: Define el atributo extra 'prioridad' para la seleccion 
 * dinamica del proceso a ejecutar.
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
    int  prioridad;     /* Numeros menores = Mayor Importancia */
    int  tiempoInicio;
    int  tiempoFin;
    int  tiempoEspera;
    int  tiempoRetorno;
    int  ejecutado;
} Proceso;

void pedirDatos(Proceso procesos[], int *cantidad);
int buscarMayorPrioridad(Proceso procesos[], int cantidad, int reloj);
void calcularTiempos(Proceso procesos[], int cantidad);
void mostrarTabla(Proceso procesos[], int cantidad);
void mostrarPromedios(Proceso procesos[], int cantidad);

#endif