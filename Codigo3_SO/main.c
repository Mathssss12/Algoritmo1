/*
 * ==========================================================================
 * Archivo: main.c
 * Proyecto: Planificacion por PRIORIDAD (No Expropiativo)
 * Descripcion: Interfaz de usuario por consola.
 * ==========================================================================
 */

#include <stdio.h>
#include "funcion.h"

int main() {
    Proceso procesos[MAX_PROCESOS];
    int cantidad = 0;
    int opcion;
    int datosIngresados = 0;

    do {
        printf("\n*** MENU PRIORIDAD ***\n");
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
                if (datosIngresados == 1) {
                    calcularTiempos(procesos, cantidad);
                    mostrarTabla(procesos, cantidad);
                    mostrarPromedios(procesos, cantidad);
                } else {
                    printf("\nError: Primero debe ingresar los datos (Opcion 1).\n");
                }
                break;
            case 3:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nError:Opcion invalida.\n");
        }
    } while (opcion != 3);

    return 0;
}