/*
 * ==========================================================================
 * Archivo: funcion.c
 * Proyecto: Planificacion por PRIORIDAD (No Expropiativo)
 * Descripcion: Simulacion donde el CPU atiende al proceso en cola que posea
 * el menor valor numerico en su campo prioridad.
 * ==========================================================================
 */

#include "funcion.h"

/*
 * Funcion: pedirDatos
 */
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
        printf("  Prioridad (1=mayor, n mayores=menor): ");
        scanf("%d", &procesos[i].prioridad);
    }
}

/*
 * Funcion: buscarMayorPrioridad
 */
int buscarMayorPrioridad(Proceso procesos[], int cantidad, int reloj) {
    int i, indiceMejor = -1;
    int mejorPrioridad = 99999; 

    for (i = 0; i < cantidad; i++) {
        if (procesos[i].ejecutado == 0 && procesos[i].tiempoLlegada <= reloj) {
            /* Se busca el numero MENOR matematicamente */
            if (procesos[i].prioridad < mejorPrioridad) {
                mejorPrioridad = procesos[i].prioridad;
                indiceMejor    = i;
            }
        }
    }
    return indiceMejor; 
}

/*
 * Funcion: calcularTiempos
 */
void calcularTiempos(Proceso procesos[], int cantidad) {
    int i, reloj = 0, terminados = 0, siguiente;

    for (i = 0; i < cantidad; i++) procesos[i].ejecutado = 0;

    while (terminados < cantidad) {
        siguiente = buscarMayorPrioridad(procesos, cantidad, reloj);

        if (siguiente == -1) {
            reloj++;
        } else {
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
    printf("\n================================================================\n");
    printf("          RESULTADOS - ALGORITMO POR PRIORIDAD                  \n");
    printf("================================================================\n");
    printf("%-8s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Proceso", "Llegada", "Duracion", "Prioridad", "Inicio", "Fin", "Espera", "Retorno");
    printf("----------------------------------------------------------------\n");
    for (i = 0; i < cantidad; i++) {
        printf("%-8s %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",
               procesos[i].nombre, procesos[i].tiempoLlegada, procesos[i].duracion,
               procesos[i].prioridad, procesos[i].tiempoInicio, procesos[i].tiempoFin,
               procesos[i].tiempoEspera, procesos[i].tiempoRetorno);
    }
    printf("================================================================\n");
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