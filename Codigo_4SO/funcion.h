/*
 * ==========================================================================
 * Archivo: funcion.h
 * Proyecto: Planificacion - Algoritmo Round Robin (RR)
 * Descripcion: Define las estructuras para el algoritmo expropiativo basado
 * en cortes de tiempo fijos (Quantum). Incluye Prioridad solo 
 * como requerimiento visual de formato.
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
    int  prioridad;      /* Exigencia visual del reporte */
    int  tiempoRestante; /* Se decrementa con cada Quantum */
    int  tiempoFin;      
    int  tiempoEspera;   
    int  tiempoRetorno;  
} Proceso;

void pedirDatos(Proceso procesos[], int *cantidad, int *quantum);
void ordenarPorLlegada(Proceso procesos[], int cantidad);
void inicializarRestante(Proceso procesos[], int cantidad);
void agregarALaCola(Proceso procesos[], int cantidad, int cola[], int *finCola, int frenteCola, int reloj, int enCola[]);
void calcularTiempos(Proceso procesos[], int cantidad, int quantum);
void mostrarTabla(Proceso procesos[], int cantidad, int quantum);
void mostrarPromedios(Proceso procesos[], int cantidad);

#endif