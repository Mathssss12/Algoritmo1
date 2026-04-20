/*
 * ==========================================================================
 * Archivo: main.c
 * Proyecto: Planificacion - Algoritmo Round Robin (RR)
 * Descripcion: Menu principal interactivo adaptado para manejar el Quantum.
 * ==========================================================================
 */

#include <stdio.h>
#include "funcion.h"

int main() {
    Proceso procesos[MAX_PROCESOS];
    int cantidad = 0;
    int quantum  = 0;
    int opcion;
    int datosIngresados = 0;

    do {
        printf("\n*** MENU ROUND ROBIN ***\n");
        printf("1. Ingresar datos de los procesos (y Quantum)\n");
        printf("2. Ver tabla de resultados\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                pedirDatos(procesos, &cantidad, &quantum);
                datosIngresados = 1;
                break;
            case 2:
                if (datosIngresados == 1) {
                    ordenarPorLlegada(procesos, cantidad);
                    calcularTiempos(procesos, cantidad, quantum);
                    mostrarTabla(procesos, cantidad, quantum);
                    mostrarPromedios(procesos, cantidad);
                } else {
                    printf("\nError: Primero debe ingresar los datos (Opcion 1).\n");
                }
                break;
            case 3:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\n Opcion invalida.\n");
        }
    } while (opcion != 3);

    return 0;
}