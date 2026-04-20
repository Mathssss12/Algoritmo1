/*
 * ==========================================================================
 * Archivo: funcion.c
 * Proyecto: Planificacion de Procesos - Algoritmo FIFO (FCFS)
 * Descripcion: Implementacion de la logica del algoritmo FIFO. Los procesos
 * se atienden estrictamente en orden de llegada sin expropiacion.
 * ==========================================================================
 */

#include "funcion.h"
void pedirDatos(Proceso procesos[], int *cantidad) {
    int i;
    printf("\nCuantos procesos desea ingresar (max %d): ", MAX_PROCESOS);
    scanf("%d", cantidad);

    for (i = 0; i < *cantidad; i++) {
        printf("\n-- Proceso %d --\n", i + 1);
        printf("  Nombre (ej. P%d): ", i + 1);
        scanf("%s", procesos[i].nombre);
        printf("  Tiempo de llegada (ms): ");
        scanf("%d", &procesos[i].tiempoLlegada);
        printf("  Duracion en CPU (ms): ");
        scanf("%d", &procesos[i].duracion);
    }
}

/*
 * Funcion: ordenarPorLlegada
 */
void ordenarPorLlegada(Proceso procesos[], int cantidad) {
    int i, j;
    Proceso temporal; 
    for (i = 0; i < cantidad - 1; i++) {
        for (j = 0; j < cantidad - 1 - i; j++) {
            if (procesos[j].tiempoLlegada > procesos[j + 1].tiempoLlegada) {
                temporal        = procesos[j];
                procesos[j]     = procesos[j + 1];
                procesos[j + 1] = temporal;
            }
        }
    }
}

/*
 * Funcion: calcularTiempos
 */
void calcularTiempos(Proceso procesos[], int cantidad) {
    int i;
    int reloj = 0; /* Simula el tiempo transcurrido en el sistema */
    
    for (i = 0; i < cantidad; i++) {
        /* Si el CPU esta inactivo esperando al proceso, el reloj avanza */
        if (reloj < procesos[i].tiempoLlegada) {
            reloj = procesos[i].tiempoLlegada;
        }
        
        procesos[i].tiempoInicio = reloj;
        procesos[i].tiempoFin = reloj + procesos[i].duracion;
        
        /* Fórmulas universales de planificacion */
        procesos[i].tiempoEspera = procesos[i].tiempoInicio - procesos[i].tiempoLlegada;
        procesos[i].tiempoRetorno = procesos[i].tiempoFin - procesos[i].tiempoLlegada;
        
        /* El reloj avanza hasta la finalizacion del proceso actual */
        reloj = procesos[i].tiempoFin;
    }
}

/* Funciones de impresion  */
void mostrarTabla(Proceso procesos[], int cantidad) {
    int i;
    printf("\n============================================================\n");
    printf("        RESULTADOS - ALGORITMO FIFO / FCFS                  \n");
    printf("============================================================\n");
    printf("%-8s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Proceso", "Llegada", "Duracion", "Inicio", "Fin", "Espera", "Retorno");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < cantidad; i++) {
        printf("%-8s %-10d %-10d %-10d %-10d %-10d %-10d\n",
               procesos[i].nombre, procesos[i].tiempoLlegada, procesos[i].duracion,
               procesos[i].tiempoInicio, procesos[i].tiempoFin,
               procesos[i].tiempoEspera, procesos[i].tiempoRetorno);
    }
    printf("============================================================\n");
}

void mostrarPromedios(Proceso procesos[], int cantidad) {
    int i;
    float sumaEspera = 0, sumaRetorno = 0;
    for (i = 0; i < cantidad; i++) {
        sumaEspera  += procesos[i].tiempoEspera;
        sumaRetorno += procesos[i].tiempoRetorno;
    }
    printf("\nPromedio tiempo de espera  : %.2f ms\n", sumaEspera / cantidad);
    printf("Promedio tiempo de retorno : %.2f ms\n", sumaRetorno / cantidad);
}