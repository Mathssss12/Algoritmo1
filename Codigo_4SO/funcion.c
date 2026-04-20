/*
 * ==========================================================================
 * Archivo: funcion.c
 * Proyecto: Planificacion - Algoritmo Round Robin (RR)
 * Descripcion: Logica avanzada utilizando una cola circular (Array) para 
 * controlar la entrada y salida expropiativa de procesos en CPU.
 * ==========================================================================
 */

#include "funcion.h"

/*
 * Funcion: pedirDatos
 */
void pedirDatos(Proceso procesos[], int *cantidad, int *quantum) {
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
        printf("  Prioridad (Solo formato visual): ");
        scanf("%d", &procesos[i].prioridad);
    }
    printf("\nValor del quantum (ms): ");
    scanf("%d", quantum);
}

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
 * Funcion: inicializarRestante
 */
void inicializarRestante(Proceso procesos[], int cantidad) {
    int i;
    for (i = 0; i < cantidad; i++) {
        procesos[i].tiempoRestante = procesos[i].duracion;
    }
}

/*
 * Funcion: agregarALaCola
 */
void agregarALaCola(Proceso procesos[], int cantidad, int cola[], int *finCola, int frenteCola, int reloj, int enCola[]) {
    int i;
    for (i = 0; i < cantidad; i++) {
        if (procesos[i].tiempoLlegada <= reloj && procesos[i].tiempoRestante > 0 && enCola[i] == 0) {
            cola[*finCola] = i; 
            (*finCola)++;
            enCola[i] = 1;      /* Marcado para evitar duplicados en la cola */
        }
    }
}

/*
 * Funcion: calcularTiempos
 */
void calcularTiempos(Proceso procesos[], int cantidad, int quantum) {
    int cola[MAX_PROCESOS * 200]; /* Buffer extenso para rotaciones multiples */
    int frente = 0, fin = 0;  
    int enCola[MAX_PROCESOS];
    int reloj = 0, actual, tiempoEjecutado, i;

    for (i = 0; i < cantidad; i++) enCola[i] = 0;
    
    inicializarRestante(procesos, cantidad);
    reloj = procesos[0].tiempoLlegada;
    agregarALaCola(procesos, cantidad, cola, &fin, frente, reloj, enCola);

    /* Ciclo mientras la cola no este vacia */
    while (frente < fin) {
        actual = cola[frente];
        frente++; /* "Desencola" al proceso actual */

        /* Determina la rafaga a ejecutar: Quantum o la fraccion restante */
        if (procesos[actual].tiempoRestante <= quantum) {
            tiempoEjecutado = procesos[actual].tiempoRestante;
        } else {
            tiempoEjecutado = quantum;
        }

        reloj += tiempoEjecutado;
        procesos[actual].tiempoRestante -= tiempoEjecutado;

        agregarALaCola(procesos, cantidad, cola, &fin, frente, reloj, enCola);

        if (procesos[actual].tiempoRestante == 0) {
            procesos[actual].tiempoFin     = reloj;
            procesos[actual].tiempoRetorno = reloj - procesos[actual].tiempoLlegada;
            procesos[actual].tiempoEspera  = procesos[actual].tiempoRetorno - procesos[actual].duracion;
        } else {
            enCola[actual] = 0;    /* Se desmarca temporalmente */
            agregarALaCola(procesos, cantidad, cola, &fin, frente, reloj, enCola);
        }
    }
}

void mostrarTabla(Proceso procesos[], int cantidad, int quantum) {
    int i;
    printf("\n========================================================================\n");
    printf("        RESULTADOS - ALGORITMO ROUND ROBIN  (Quantum = %d ms)           \n", quantum);
    printf("========================================================================\n");
    /* Imprime la columna de prioridad como requisito visual de la tabla */
    printf("%-8s %-10s %-10s %-11s %-10s %-10s %-10s\n",
           "Proceso", "Llegada", "Duracion", "Prioridad", "Fin", "Espera", "Retorno");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < cantidad; i++) {
        printf("%-8s %-10d %-10d %-11d %-10d %-10d %-10d\n",
               procesos[i].nombre, procesos[i].tiempoLlegada, procesos[i].duracion,
               procesos[i].prioridad, procesos[i].tiempoFin,
               procesos[i].tiempoEspera, procesos[i].tiempoRetorno);
    }
    printf("========================================================================\n");
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