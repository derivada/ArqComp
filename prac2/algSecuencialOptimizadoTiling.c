#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define ALG_NAME "secOptTiling"
#define BLOCK_SIZE 8
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algSecOptTiling(datos in);

// Variables del experimento
int N, semilla;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    // Inicializamos y aoques de buclesrueba, N, semilla);
    inicializacion(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algSecOptTiling, *casoPrueba);

    // Imprimimos los resultados
    if (DEBUG_MSG)
        printf("Tiempos: ck = %d\tck_medio = %4lf\n", results.ck, results.ck_medios);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s,%lf\n", N, ALG_NAME, results.ck_medios);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

int algSecOptTiling(datos in)
{
    /**
     * OPTIMIZACIONES REALIZADAS
     * 3. Tiling en los bucles i y j
     */
    int bi = 0, bj = 0, i, j, iLimit, jLimit;
    for (; bi < N; bi += BLOCK_SIZE)
    { // N / BLOCK_SIZE (div. entera) iteraciones
        for (; bj < N; bj += BLOCK_SIZE)
        { // N / BLOCK_SIZE (div. entera) iteraciones
            iLimit = bi + BLOCK_SIZE;
            if (iLimit > N)
                iLimit = N;
            for (i = bi; i < iLimit; i++)
            { // BLOCK_SIZE iteraciones
                jLimit = bj + BLOCK_SIZE;
                if (jLimit > N)
                    jLimit = N;
                for (j = bj; j < jLimit; j++)
                { // BLOCK_SIZE iteraciones
                    for (int k = 0; k < 8; k++)
                    {                                                          // 8 iteraciones
                        in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]); // 9 accesos
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {                                             // N iteraciones
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2; // 5 accesos
        in.f += in.e[i];                          // 2 accesos
    }
    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial por tiling: f = %4lf\n", in.f);

    // accesos = (9*8*N*N) + (N*5*2)    // Inicializamos el contador
    int accesos = N * (72 * N + 10);
    return accesos;
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
