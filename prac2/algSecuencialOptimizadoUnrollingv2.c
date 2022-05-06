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
    int newN = N - (N % 4);
    for (int i = 0; i < N; i++)
    { // N iteraciones
        int j = 0;
        d[i] = (double *)malloc(sizeof(double) * N);
        for (; j < newN; j += 4)
        { // N iteraciones
            // 72 accesos
            // AREA J = 0
            d[i][j] += 2 * in.a[i][0] * (in.b[0][j] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
            // AREA J = 1
            int a = j + 1;
            d[i][a] += 2 * in.a[i][0] * (in.b[0][a] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][a] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][a] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][a] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][a] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][a] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][a] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][a] - in.c[7]);
            // AREA J = 2
            int b = j + 2;
            d[i][b] += 2 * in.a[i][0] * (in.b[0][b] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][b] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][b] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][b] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][b] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][b] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][b] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][b] - in.c[7]);
            // AREA J = 3
            int c = j + 3;
            d[i][c] += 2 * in.a[i][0] * (in.b[0][c] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][c] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][c] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][c] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][c] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][c] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][c] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][c] - in.c[7]);
        }
        while (j < N)
        {
            d[i][j] += 2 * in.a[i][0] * (in.b[0][j] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
            j++;
        }
    }

    int i = 0;
    for (; i < newN; i += 4)
    {
        e[i] = d[in.ind[i]][in.ind[i]] / 2;
        free(d[in.ind[i]]);
        int a = i + 1;
        e[a] = d[in.ind[a]][in.ind[a]] / 2;
        free(d[in.ind[a]]);
        int b = i + 2;
        e[b] = d[in.ind[b]][in.ind[b]] / 2;
        free(d[in.ind[b]]);
        int c = i + 3;
        e[c] = d[in.ind[c]][in.ind[c]] / 2;
        free(d[in.ind[c]]);
        f += e[i] + e[a] + e[b] + e[c];
    }

    while (i < N)
    {
        e[i] = d[in.ind[i]][in.ind[i]] / 2;
        free(d[in.ind[i]]);
        f += e[i];
        i++;
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
