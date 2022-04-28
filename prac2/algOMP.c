#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include "utils.h"

#define ALG_NAME "algOmp_"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algoritmoOMP(datos in);

// Variables del experimento
int N, semilla, numThreads;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;
    omp_set_num_threads(numThreads);
    // Inicializamos y aleatoriazamos el caso de prueba
    inicializacion(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algoritmoOMP, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s%d,%d,%lf,%lf\n", N, ALG_NAME, numThreads, results.ck, results.ck_medios, results.microsegundos);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

int algoritmoOMP(datos in)
{
    int i = 0;
#pragma omp parallel for
    for (i = 0; i < N; i++)
    { // N iteraciones
        int j;
        for (j = 0; j < N / 4; j += 4)
        { // N iteraciones
            // 72 accesos
            // AREA J = 0
            int a = j + 1;
            int b = j + 2;
            int c = j + 3;
            in.d[i][j] += 2 * in.a[i][0] * (in.b[0][j] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
            // AREA J = 1
            in.d[i][a] += 2 * in.a[i][0] * (in.b[0][a] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][a] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][a] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][a] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][a] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][a] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][a] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][a] - in.c[7]);
            // AREA J = 2
            in.d[i][b] += 2 * in.a[i][0] * (in.b[0][b] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][b] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][b] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][b] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][b] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][b] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][b] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][b] - in.c[7]);
            // AREA J = 3
            in.d[i][c] += 2 * in.a[i][0] * (in.b[0][c] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][c] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][c] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][c] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][c] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][c] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][c] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][c] - in.c[7]);
        }
        while (j < N)
        {
            in.d[i][j] += 2 * in.a[i][0] * (in.b[0][j] - in.c[0]) + 2 * in.a[i][1] * (in.b[1][j] - in.c[1]) + 2 * in.a[i][2] * (in.b[2][j] - in.c[2]) + 2 * in.a[i][3] * (in.b[3][j] - in.c[3]) + 2 * in.a[i][4] * (in.b[4][j] - in.c[4]) + 2 * in.a[i][5] * (in.b[5][j] - in.c[5]) + 2 * in.a[i][6] * (in.b[6][j] - in.c[6]) + 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
            j++;
        }
    }
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {                                             // N iteraciones
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2; // 5 accesos
#pragma omp atomic
        in.f += in.e[i]; // 2 accesos
    }

    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial por OpenMP: f = %4lf\n", in.f);
    int accesos = N * (72 * N + 10);
    return accesos;
}

void leerParametros(int argc, const char *argv[])
{
    if (argc != 5)
    {
        printf("Uso correcto: ./main NUM_THREADS N SEM_ALEAT OUTPUT_FILE\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // N: tamaño de la operación
        numThreads = atoi(argv[1]);
        N = atoi(argv[2]);
        semilla = atoi(argv[3]);
        if ((outputFile = fopen(argv[4], "a")) == NULL) // Abrimos el archivo de salida
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
