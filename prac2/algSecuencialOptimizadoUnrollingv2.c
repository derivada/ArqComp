#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define ALG_NAME "OptUnroll_V4"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
void algSecOptUnroll2(datos in);

// Variables del experimento
int N, semilla;
char *optimizationFlag;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    // Inicializamos y aoques de buclesrueba, N, semilla);
    inicializacion(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    if (N % 50 != 0)
    {
        printf("N debe ser divisible entre 50 en el programa de unrolling\n");
        exit(EXIT_FAILURE);
    }
    results = medirTiempoEjecucion(algSecOptUnroll2, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (%s),%d,%lf\n",
            N, ALG_NAME, optimizationFlag, results.ciclos, results.microsegundos);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

void algSecOptUnroll2(datos in)
{
    /**
     * OPTIMIZACIONES REALIZADAS
     * 3. Unrolling del bucle de las k y las j
     */

    double **d = (double **)malloc(sizeof(double *) * N);
    double *e = (double *)malloc(sizeof(double) * N);
    double f = 0;
    for (int i = 0; i < N; i++)
    {
        d[i] = (double *)malloc(sizeof(double) * N);
        for (int j = 0; j < N; j += 50)
        {
            d[i][j] = 2 * in.a[i][0] * (in.b[0][j] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
            int j1 = j + 1;
            d[i][j1] = 2 * in.a[i][0] * (in.b[0][j1] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j1] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j1] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j1] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j1] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j1] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j1] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j1] - in.c[7]);
            int j2 = j + 2;
            d[i][j2] = 2 * in.a[i][0] * (in.b[0][j2] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j2] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j2] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j2] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j2] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j2] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j2] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j2] - in.c[7]);
            int j3 = j + 3;
            d[i][j3] = 2 * in.a[i][0] * (in.b[0][j3] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j3] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j3] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j3] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j3] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j3] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j3] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j3] - in.c[7]);
            int j4 = j + 4;
            d[i][j4] = 2 * in.a[i][0] * (in.b[0][j4] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j4] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j4] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j4] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j4] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j4] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j4] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j4] - in.c[7]);
            int j5 = j + 5;
            d[i][j5] = 2 * in.a[i][0] * (in.b[0][j5] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j5] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j5] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j5] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j5] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j5] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j5] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j5] - in.c[7]);
            int j6 = j + 6;
            d[i][j6] = 2 * in.a[i][0] * (in.b[0][j6] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j6] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j6] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j6] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j6] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j6] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j6] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j6] - in.c[7]);
            int j7 = j + 7;
            d[i][j7] = 2 * in.a[i][0] * (in.b[0][j7] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j7] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j7] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j7] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j7] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j7] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j7] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j7] - in.c[7]);
            int j8 = j + 8;
            d[i][j8] = 2 * in.a[i][0] * (in.b[0][j8] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j8] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j8] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j8] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j8] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j8] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j8] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j8] - in.c[7]);
            int j9 = j + 9;
            d[i][j9] = 2 * in.a[i][0] * (in.b[0][j9] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j9] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j9] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j9] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j9] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j9] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j9] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j9] - in.c[7]);
            int j10 = j + 10;
            d[i][j10] = 2 * in.a[i][0] * (in.b[0][j10] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j10] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j10] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j10] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j10] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j10] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j10] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j10] - in.c[7]);
            int j11 = j + 11;
            d[i][j11] = 2 * in.a[i][0] * (in.b[0][j11] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j11] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j11] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j11] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j11] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j11] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j11] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j11] - in.c[7]);
            int j12 = j + 12;
            d[i][j12] = 2 * in.a[i][0] * (in.b[0][j12] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j12] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j12] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j12] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j12] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j12] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j12] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j12] - in.c[7]);
            int j13 = j + 13;
            d[i][j13] = 2 * in.a[i][0] * (in.b[0][j13] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j13] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j13] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j13] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j13] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j13] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j13] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j13] - in.c[7]);
            int j14 = j + 14;
            d[i][j14] = 2 * in.a[i][0] * (in.b[0][j14] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j14] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j14] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j14] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j14] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j14] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j14] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j14] - in.c[7]);
            int j15 = j + 15;
            d[i][j15] = 2 * in.a[i][0] * (in.b[0][j15] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j15] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j15] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j15] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j15] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j15] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j15] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j15] - in.c[7]);
            int j16 = j + 16;
            d[i][j16] = 2 * in.a[i][0] * (in.b[0][j16] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j16] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j16] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j16] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j16] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j16] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j16] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j16] - in.c[7]);
            int j17 = j + 17;
            d[i][j17] = 2 * in.a[i][0] * (in.b[0][j17] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j17] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j17] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j17] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j17] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j17] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j17] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j17] - in.c[7]);
            int j18 = j + 18;
            d[i][j18] = 2 * in.a[i][0] * (in.b[0][j18] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j18] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j18] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j18] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j18] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j18] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j18] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j18] - in.c[7]);
            int j19 = j + 19;
            d[i][j19] = 2 * in.a[i][0] * (in.b[0][j19] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j19] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j19] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j19] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j19] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j19] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j19] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j19] - in.c[7]);
            int j20 = j + 20;
            d[i][j20] = 2 * in.a[i][0] * (in.b[0][j20] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j20] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j20] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j20] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j20] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j20] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j20] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j20] - in.c[7]);
            int j21 = j + 21;
            d[i][j21] = 2 * in.a[i][0] * (in.b[0][j21] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j21] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j21] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j21] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j21] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j21] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j21] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j21] - in.c[7]);
            int j22 = j + 22;
            d[i][j22] = 2 * in.a[i][0] * (in.b[0][j22] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j22] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j22] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j22] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j22] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j22] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j22] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j22] - in.c[7]);
            int j23 = j + 23;
            d[i][j23] = 2 * in.a[i][0] * (in.b[0][j23] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j23] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j23] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j23] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j23] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j23] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j23] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j23] - in.c[7]);
            int j24 = j + 24;
            d[i][j24] = 2 * in.a[i][0] * (in.b[0][j24] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j24] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j24] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j24] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j24] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j24] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j24] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j24] - in.c[7]);
            int j25 = j + 25;
            d[i][j25] = 2 * in.a[i][0] * (in.b[0][j25] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j25] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j25] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j25] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j25] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j25] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j25] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j25] - in.c[7]);
            int j26 = j + 26;
            d[i][j26] = 2 * in.a[i][0] * (in.b[0][j26] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j26] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j26] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j26] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j26] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j26] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j26] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j26] - in.c[7]);
            int j27 = j + 27;
            d[i][j27] = 2 * in.a[i][0] * (in.b[0][j27] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j27] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j27] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j27] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j27] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j27] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j27] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j27] - in.c[7]);
            int j28 = j + 28;
            d[i][j28] = 2 * in.a[i][0] * (in.b[0][j28] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j28] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j28] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j28] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j28] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j28] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j28] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j28] - in.c[7]);
            int j29 = j + 29;
            d[i][j29] = 2 * in.a[i][0] * (in.b[0][j29] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j29] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j29] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j29] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j29] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j29] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j29] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j29] - in.c[7]);
            int j30 = j + 30;
            d[i][j30] = 2 * in.a[i][0] * (in.b[0][j30] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j30] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j30] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j30] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j30] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j30] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j30] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j30] - in.c[7]);
            int j31 = j + 31;
            d[i][j31] = 2 * in.a[i][0] * (in.b[0][j31] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j31] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j31] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j31] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j31] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j31] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j31] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j31] - in.c[7]);
            int j32 = j + 32;
            d[i][j32] = 2 * in.a[i][0] * (in.b[0][j32] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j32] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j32] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j32] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j32] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j32] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j32] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j32] - in.c[7]);
            int j33 = j + 33;
            d[i][j33] = 2 * in.a[i][0] * (in.b[0][j33] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j33] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j33] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j33] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j33] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j33] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j33] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j33] - in.c[7]);
            int j34 = j + 34;
            d[i][j34] = 2 * in.a[i][0] * (in.b[0][j34] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j34] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j34] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j34] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j34] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j34] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j34] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j34] - in.c[7]);
            int j35 = j + 35;
            d[i][j35] = 2 * in.a[i][0] * (in.b[0][j35] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j35] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j35] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j35] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j35] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j35] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j35] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j35] - in.c[7]);
            int j36 = j + 36;
            d[i][j36] = 2 * in.a[i][0] * (in.b[0][j36] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j36] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j36] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j36] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j36] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j36] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j36] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j36] - in.c[7]);
            int j37 = j + 37;
            d[i][j37] = 2 * in.a[i][0] * (in.b[0][j37] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j37] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j37] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j37] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j37] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j37] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j37] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j37] - in.c[7]);
            int j38 = j + 38;
            d[i][j38] = 2 * in.a[i][0] * (in.b[0][j38] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j38] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j38] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j38] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j38] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j38] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j38] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j38] - in.c[7]);
            int j39 = j + 39;
            d[i][j39] = 2 * in.a[i][0] * (in.b[0][j39] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j39] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j39] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j39] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j39] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j39] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j39] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j39] - in.c[7]);
            int j40 = j + 40;
            d[i][j40] = 2 * in.a[i][0] * (in.b[0][j40] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j40] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j40] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j40] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j40] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j40] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j40] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j40] - in.c[7]);
            int j41 = j + 41;
            d[i][j41] = 2 * in.a[i][0] * (in.b[0][j41] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j41] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j41] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j41] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j41] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j41] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j41] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j41] - in.c[7]);
            int j42 = j + 42;
            d[i][j42] = 2 * in.a[i][0] * (in.b[0][j42] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j42] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j42] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j42] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j42] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j42] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j42] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j42] - in.c[7]);
            int j43 = j + 43;
            d[i][j43] = 2 * in.a[i][0] * (in.b[0][j43] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j43] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j43] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j43] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j43] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j43] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j43] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j43] - in.c[7]);
            int j44 = j + 44;
            d[i][j44] = 2 * in.a[i][0] * (in.b[0][j44] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j44] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j44] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j44] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j44] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j44] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j44] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j44] - in.c[7]);
            int j45 = j + 45;
            d[i][j45] = 2 * in.a[i][0] * (in.b[0][j45] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j45] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j45] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j45] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j45] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j45] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j45] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j45] - in.c[7]);
            int j46 = j + 46;
            d[i][j46] = 2 * in.a[i][0] * (in.b[0][j46] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j46] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j46] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j46] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j46] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j46] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j46] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j46] - in.c[7]);
            int j47 = j + 47;
            d[i][j47] = 2 * in.a[i][0] * (in.b[0][j47] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j47] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j47] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j47] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j47] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j47] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j47] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j47] - in.c[7]);
            int j48 = j + 48;
            d[i][j48] = 2 * in.a[i][0] * (in.b[0][j48] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j48] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j48] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j48] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j48] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j48] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j48] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j48] - in.c[7]);
            int j49 = j + 49;
            d[i][j49] = 2 * in.a[i][0] * (in.b[0][j49] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j49] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j49] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j49] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j49] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j49] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j49] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j49] - in.c[7]);
        }
    }

    for (int j = 0; j < N; j += 50)
    {
        e[j] = d[in.ind[j]][in.ind[j]] / 2;
        free(d[in.ind[j]]);
        int j1 = j + 1;
        e[j1] = d[in.ind[j1]][in.ind[j1]] / 2;
        free(d[in.ind[j1]]);
        int j2 = j + 2;
        e[j2] = d[in.ind[j2]][in.ind[j2]] / 2;
        free(d[in.ind[j2]]);
        int j3 = j + 3;
        e[j3] = d[in.ind[j3]][in.ind[j3]] / 2;
        free(d[in.ind[j3]]);
        int j4 = j + 4;
        e[j4] = d[in.ind[j4]][in.ind[j4]] / 2;
        free(d[in.ind[j4]]);
        int j5 = j + 5;
        e[j5] = d[in.ind[j5]][in.ind[j5]] / 2;
        free(d[in.ind[j5]]);
        int j6 = j + 6;
        e[j6] = d[in.ind[j6]][in.ind[j6]] / 2;
        free(d[in.ind[j6]]);
        int j7 = j + 7;
        e[j7] = d[in.ind[j7]][in.ind[j7]] / 2;
        free(d[in.ind[j7]]);
        int j8 = j + 8;
        e[j8] = d[in.ind[j8]][in.ind[j8]] / 2;
        free(d[in.ind[j8]]);
        int j9 = j + 9;
        e[j9] = d[in.ind[j9]][in.ind[j9]] / 2;
        free(d[in.ind[j9]]);
        int j10 = j + 10;
        e[j10] = d[in.ind[j10]][in.ind[j10]] / 2;
        free(d[in.ind[j10]]);
        int j11 = j + 11;
        e[j11] = d[in.ind[j11]][in.ind[j11]] / 2;
        free(d[in.ind[j11]]);
        int j12 = j + 12;
        e[j12] = d[in.ind[j12]][in.ind[j12]] / 2;
        free(d[in.ind[j12]]);
        int j13 = j + 13;
        e[j13] = d[in.ind[j13]][in.ind[j13]] / 2;
        free(d[in.ind[j13]]);
        int j14 = j + 14;
        e[j14] = d[in.ind[j14]][in.ind[j14]] / 2;
        free(d[in.ind[j14]]);
        int j15 = j + 15;
        e[j15] = d[in.ind[j15]][in.ind[j15]] / 2;
        free(d[in.ind[j15]]);
        int j16 = j + 16;
        e[j16] = d[in.ind[j16]][in.ind[j16]] / 2;
        free(d[in.ind[j16]]);
        int j17 = j + 17;
        e[j17] = d[in.ind[j17]][in.ind[j17]] / 2;
        free(d[in.ind[j17]]);
        int j18 = j + 18;
        e[j18] = d[in.ind[j18]][in.ind[j18]] / 2;
        free(d[in.ind[j18]]);
        int j19 = j + 19;
        e[j19] = d[in.ind[j19]][in.ind[j19]] / 2;
        free(d[in.ind[j19]]);
        int j20 = j + 20;
        e[j20] = d[in.ind[j20]][in.ind[j20]] / 2;
        free(d[in.ind[j20]]);
        int j21 = j + 21;
        e[j21] = d[in.ind[j21]][in.ind[j21]] / 2;
        free(d[in.ind[j21]]);
        int j22 = j + 22;
        e[j22] = d[in.ind[j22]][in.ind[j22]] / 2;
        free(d[in.ind[j22]]);
        int j23 = j + 23;
        e[j23] = d[in.ind[j23]][in.ind[j23]] / 2;
        free(d[in.ind[j23]]);
        int j24 = j + 24;
        e[j24] = d[in.ind[j24]][in.ind[j24]] / 2;
        free(d[in.ind[j24]]);
        int j25 = j + 25;
        e[j25] = d[in.ind[j25]][in.ind[j25]] / 2;
        free(d[in.ind[j25]]);
        int j26 = j + 26;
        e[j26] = d[in.ind[j26]][in.ind[j26]] / 2;
        free(d[in.ind[j26]]);
        int j27 = j + 27;
        e[j27] = d[in.ind[j27]][in.ind[j27]] / 2;
        free(d[in.ind[j27]]);
        int j28 = j + 28;
        e[j28] = d[in.ind[j28]][in.ind[j28]] / 2;
        free(d[in.ind[j28]]);
        int j29 = j + 29;
        e[j29] = d[in.ind[j29]][in.ind[j29]] / 2;
        free(d[in.ind[j29]]);
        int j30 = j + 30;
        e[j30] = d[in.ind[j30]][in.ind[j30]] / 2;
        free(d[in.ind[j30]]);
        int j31 = j + 31;
        e[j31] = d[in.ind[j31]][in.ind[j31]] / 2;
        free(d[in.ind[j31]]);
        int j32 = j + 32;
        e[j32] = d[in.ind[j32]][in.ind[j32]] / 2;
        free(d[in.ind[j32]]);
        int j33 = j + 33;
        e[j33] = d[in.ind[j33]][in.ind[j33]] / 2;
        free(d[in.ind[j33]]);
        int j34 = j + 34;
        e[j34] = d[in.ind[j34]][in.ind[j34]] / 2;
        free(d[in.ind[j34]]);
        int j35 = j + 35;
        e[j35] = d[in.ind[j35]][in.ind[j35]] / 2;
        free(d[in.ind[j35]]);
        int j36 = j + 36;
        e[j36] = d[in.ind[j36]][in.ind[j36]] / 2;
        free(d[in.ind[j36]]);
        int j37 = j + 37;
        e[j37] = d[in.ind[j37]][in.ind[j37]] / 2;
        free(d[in.ind[j37]]);
        int j38 = j + 38;
        e[j38] = d[in.ind[j38]][in.ind[j38]] / 2;
        free(d[in.ind[j38]]);
        int j39 = j + 39;
        e[j39] = d[in.ind[j39]][in.ind[j39]] / 2;
        free(d[in.ind[j39]]);
        int j40 = j + 40;
        e[j40] = d[in.ind[j40]][in.ind[j40]] / 2;
        free(d[in.ind[j40]]);
        int j41 = j + 41;
        e[j41] = d[in.ind[j41]][in.ind[j41]] / 2;
        free(d[in.ind[j41]]);
        int j42 = j + 42;
        e[j42] = d[in.ind[j42]][in.ind[j42]] / 2;
        free(d[in.ind[j42]]);
        int j43 = j + 43;
        e[j43] = d[in.ind[j43]][in.ind[j43]] / 2;
        free(d[in.ind[j43]]);
        int j44 = j + 44;
        e[j44] = d[in.ind[j44]][in.ind[j44]] / 2;
        free(d[in.ind[j44]]);
        int j45 = j + 45;
        e[j45] = d[in.ind[j45]][in.ind[j45]] / 2;
        free(d[in.ind[j45]]);
        int j46 = j + 46;
        e[j46] = d[in.ind[j46]][in.ind[j46]] / 2;
        free(d[in.ind[j46]]);
        int j47 = j + 47;
        e[j47] = d[in.ind[j47]][in.ind[j47]] / 2;
        free(d[in.ind[j47]]);
        int j48 = j + 48;
        e[j48] = d[in.ind[j48]][in.ind[j48]] / 2;
        free(d[in.ind[j48]]);
        int j49 = j + 49;
        e[j49] = d[in.ind[j49]][in.ind[j49]] / 2;
        free(d[in.ind[j49]]);

        f += e[j] + e[j1] + e[j2] + e[j3] + e[j4] + e[j5] + e[j6] + e[j7] + e[j8] + e[j9] +
             e[j10] + e[j11] + e[j12] + e[j13] + e[j14] + e[j15] + e[j16] + e[j17] + e[j18] + e[j19] +
             e[j20] + e[j21] + e[j22] + e[j23] + e[j24] + e[j25] + e[j26] + e[j27] + e[j28] + e[j29] +
             e[j30] + e[j31] + e[j32] + e[j33] + e[j34] + e[j35] + e[j36] + e[j37] + e[j38] + e[j39] +
             e[j40] + e[j41] + e[j42] + e[j43] + e[j44] + e[j45] + e[j46] + e[j47] + e[j48] + e[j49];
    }
    free(d);
    free(e);

    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial por unrolling (v2): f = %4lf\n", f);
}

void leerParametros(int argc, const char *argv[])
{
    if (argc != 4)
    {
        printf("Uso correcto: ./main N SEM_ALEAT OUTPUT_FILE\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        optimizationFlag = (char *)malloc(3 * sizeof(char));
        strncpy(optimizationFlag, argv[0] + (strlen(argv[0]) - 4), 2);
        *(optimizationFlag + 2) = '\0';
        // N: tamaño de la operación
        N = atoi(argv[1]);
        semilla = atoi(argv[2]);
        if ((outputFile = fopen(argv[3], "a")) == NULL) // Abrimos el archivo de salida
        {
            printf("Error al abrir el archivo de salida\n");
            exit(EXIT_FAILURE);
        }
        on_exit(cerrarArchivoSalida, NULL); // Al acabar cerramos el archivo de salida!
        if (N <= 0)                         // Comprobamos que los valores de entrada son válidos
        {
            printf("Alguno de los argumentos numéricos es incorrecto\n");
            exit(EXIT_FAILURE);
        }
    }
}

void cerrarArchivoSalida(int status, void *args)
{
    fclose(outputFile);
}
