/*
 * ==========================================================================
 * Archivo: funcion.c
 * Proyecto: Planificacion - Algoritmo SJF (No Expropiativo)
 * Descripcion: Implementacion de busqueda selectiva. El CPU prioriza la 
 * rafaga menor de entre los procesos ya encolados.
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
 * Funcion: buscarMasCorto
 */
int buscarMasCorto(Proceso procesos[], int cantidad, int reloj) {
    int i, indiceMenor = -1;
    int menorDuracion = 99999; /* Umbral alto para facilitar la comparacion */

    for (i = 0; i < cantidad; i++) {
        if (procesos[i].ejecutado == 0 && procesos[i].tiempoLlegada <= reloj) {
            if (procesos[i].duracion < menorDuracion) {
                menorDuracion = procesos[i].duracion;
                indiceMenor   = i;
            }
        }
    }
    return indiceMenor; 
}

/*
 * Funcion: calcularTiempos
 */
void calcularTiempos(Proceso procesos[], int cantidad) {
    int i, reloj = 0, terminados = 0, siguiente;

    /* Inicializar banderas */
    for (i = 0; i < cantidad; i++) procesos[i].ejecutado = 0;

    while (terminados < cantidad) {
        siguiente = buscarMasCorto(procesos, cantidad, reloj);

        if (siguiente == -1) {
            /* Tiempo muerto del procesador */
            reloj++;
        } else {
            /* Ejecucion del proceso mas corto */
            procesos[siguiente].tiempoInicio = reloj;
            procesos[siguiente].tiempoFin = reloj + procesos[siguiente].duracion;
            procesos[siguiente].tiempoEspera = procesos[siguiente].tiempoInicio - procesos[siguiente].tiempoLlegada;
            procesos[siguiente].tiempoRetorno = procesos[siguiente].tiempoFin - procesos[siguiente].tiempoLlegada;
            
            reloj = procesos[siguiente].tiempoFin;
            procesos[siguiente].ejecutado = 1;
            terminados++;
        }
    }
}

void mostrarTabla(Proceso procesos[], int cantidad) {
    int i;
    printf("\n============================================================\n");
    printf("           RESULTADOS - ALGORITMO SJF                       \n");
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