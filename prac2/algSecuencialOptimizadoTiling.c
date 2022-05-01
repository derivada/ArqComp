#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define ALG_NAME "OptTiling"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algSecOptTiling(datos in);

// Variables del experimento
int N, semilla, blockSize;
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
    results = medirTiempoEjecucion(algSecOptTiling, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (tile = %d) (%s),%d,%lf, %lf\n",
            N, ALG_NAME, blockSize, optimizationFlag, results.ck, results.ck_medios, results.microsegundos);

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
    for (int bi = 0; bi < N; bi += blockSize)
    { // N / blockSize (div. entera) iteraciones
        for (int bj = 0; bj < N; bj += blockSize)
        { // N / blockSize (div. entera) iteraciones
            int iLimit = bi + blockSize;
            if (iLimit > N)
                iLimit = N;
            for (int i = bi; i < iLimit; i++)
            { // blockSize iteraciones
                int jLimit = bj + blockSize;
                if (jLimit > N)
                    jLimit = N;
                for (int j = bj; j < jLimit; j++)
                { // blockSize iteraciones
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
        printf("Resultado del algoritmo secuencial por tiling (bs = %d): f = %4lf\n",
               blockSize, in.f);

    // accesos = (9*8*N*N) + (N*5*2)    // Inicializamos el contador
    int accesos = N * (72 * N + 10);
    return accesos;
}

void leerParametros(int argc, const char *argv[])
{
    if (argc != 5)
    {
        printf("Uso correcto: ./main BLOCK_SIZE N SEM_ALEAT OUTPUT_FILE \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        optimizationFlag = (char *)malloc(3 * sizeof(char));
        strncpy(optimizationFlag, argv[0] + (strlen(argv[0]) - 4), 2);
        *(optimizationFlag + 2) = '\0';
        
        blockSize = atoi(argv[1]);
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
