/*
 * ==========================================================================
 * Archivo: main.c
 * Proyecto: Planificacion de Procesos - Algoritmo FIFO (FCFS)
 * Descripcion: Archivo principal que orquesta el flujo del programa a traves
 * de un menu interactivo (switch-case).
 * ==========================================================================
 */

#include <stdio.h>
#include "funcion.h"

int main() {
    Proceso procesos[MAX_PROCESOS];
    int cantidad = 0;
    int opcion;
    int datosIngresados = 0; /* Bandera de validacion */

    do {
        printf("\n*** MENU FIFO ***\n");
        printf("1. Ingresar datos de los procesos\n");
        printf("2. Ver tabla de resultados\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                pedirDatos(procesos, &cantidad);
                datosIngresados = 1;
                break;
            case 2:
                /* Validacion para evitar procesar basura en memoria */
                if (datosIngresados == 1) {
                    ordenarPorLlegada(procesos, cantidad);
                    calcularTiempos(procesos, cantidad);
                    mostrarTabla(procesos, cantidad);
                    mostrarPromedios(procesos, cantidad);
                } else {
                    printf("\nError: Primero debe ingresar los datos.\n");
                }
                break;
            case 3:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    return 0;
}