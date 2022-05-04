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
int N, semilla, rowBlockSize, colBlockSize;
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
    fprintf(outputFile, "%d,%s (tile = %dx%d) (%s),%d,%lf, %lf\n",
            N, ALG_NAME, rowBlockSize, colBlockSize, optimizationFlag, results.ck, results.ck_medios, results.microsegundos);

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

    for (int j = 0; j < N; j++)
    {
        in.b[0][j] -= in.c[0];
        in.b[1][j] -= in.c[1];
        in.b[2][j] -= in.c[2];
        in.b[3][j] -= in.c[3];
        in.b[4][j] -= in.c[4];
        in.b[5][j] -= in.c[5];
        in.b[6][j] -= in.c[6];
        in.b[7][j] -= in.c[7];
    }

    // D = 2 * A x B
    // ORIGINAL: in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]);
    double acc00, acc01, acc10, acc11;
    for (int ii = 0; ii < N; ii += rowBlockSize)
    {
        for (int jj = 0; jj < N; jj += colBlockSize)
        {
            int minCol = jj + colBlockSize;
            if (minCol > N)
                minCol = N;
            for (int j = 0; j < N; j += 2)
            {
                int minRow = ii + rowBlockSize;
                if (minRow > N)
                    minRow = N;
                for (int i = ii; i < minRow; i += 2)
                {
                    acc00 = 0, acc01 = 0, acc10 = 0, acc11 = 0;
                    for (int k = 0; k < 8; k++)
                    {
                        acc00 += in.b[k][j + 0] * in.a[i + 0][k];
                        acc01 += in.b[k][j + 1] * in.a[i + 0][k];
                        acc10 += in.b[k][j + 0] * in.a[i + 1][k];
                        acc11 += in.b[k][j + 1] * in.a[i + 1][k];
                    }
                    in.d[i + 0][j + 0] = acc00 * 2;
                    in.d[i + 0][j + 1] = acc01 * 2;
                    in.d[i + 1][j + 0] = acc10 * 2;
                    in.d[i + 1][j + 1] = acc11 * 2;
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
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N - 1; j++)
            {
                printf("%4lf, ", in.d[i][j]);
            }
            printf("%4lf\n", in.d[i][N - 1]);
        }
        printf("\n");

        printf("Resultado del algoritmo secuencial por tiling (bs = %dx%d): f = %4lf\n",
               rowBlockSize, colBlockSize, in.f);
    }

    // accesos = (9*8*N*N) + (N*5*2)    // Inicializamos el contador
    int accesos = N * (72 * N + 10);
    return accesos;
}

void leerParametros(int argc, const char *argv[])
{
    if (argc != 6)
    {
        printf("Uso correcto: ./main ROW_BS COL_BS N SEM_ALEAT OUTPUT_FILE \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        optimizationFlag = (char *)malloc(3 * sizeof(char));
        strncpy(optimizationFlag, argv[0] + (strlen(argv[0]) - 4), 2);
        *(optimizationFlag + 2) = '\0';

        rowBlockSize = atoi(argv[1]);
        colBlockSize = atoi(argv[2]);
        N = atoi(argv[3]);
        semilla = atoi(argv[4]);

        if ((outputFile = fopen(argv[5], "a")) == NULL) // Abrimos el archivo de salida
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
