#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define ALG_NAME "OptUnrollOld"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algSecOptUnroll1(datos in);

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
    results = medirTiempoEjecucion(algSecOptUnroll1, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (%s),%d,%lf,%lf\n",
            N, ALG_NAME, optimizationFlag, results.ck, results.ck_medios, results.microsegundos);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

int algSecOptUnroll1(datos in)
{
    /**
     * OPTIMIZACIONES REALIZADAS
     * 2. Unrolling del bucle de las k
     */
    for (int i = 0; i < N; i++)
    { // N iteraciones
        for (int j = 0; j < N; j++)
        { // N iteraciones
            // 72 accesos
            in.d[i][j] += 2 * in.a[i][0] * (in.b[0][j] - in.c[0]);
            in.d[i][j] += 2 * in.a[i][1] * (in.b[1][j] - in.c[1]);
            in.d[i][j] += 2 * in.a[i][2] * (in.b[2][j] - in.c[2]);
            in.d[i][j] += 2 * in.a[i][3] * (in.b[3][j] - in.c[3]);
            in.d[i][j] += 2 * in.a[i][4] * (in.b[4][j] - in.c[4]);
            in.d[i][j] += 2 * in.a[i][5] * (in.b[5][j] - in.c[5]);
            in.d[i][j] += 2 * in.a[i][6] * (in.b[6][j] - in.c[6]);
            in.d[i][j] += 2 * in.a[i][7] * (in.b[7][j] - in.c[7]);
        }
    }

    for (int i = 0; i < N; i++)
    {                                             // N iteraciones
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2; // 5 accesos
        in.f += in.e[i];                          // 2 accesos
    }

    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial por unrolling (v1): f = %4lf\n", in.f);

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
