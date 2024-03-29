#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define ALG_NAME "OptOrden"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
void algSecOptOrden(datos in);

// Variables del experimento
int N, semilla;
char *optimizationFlag;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    // Inicializamos y aleatoriazamos el caso de prueba
    inicializacion(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algSecOptOrden, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (%s),%d,%lf\n",
            N, ALG_NAME, optimizationFlag, results.ciclos, results.microsegundos);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

void algSecOptOrden(datos in)
{
    /**
     * OPTIMIZACIONES REALIZADAS
     * 1. Cambiar de orden los bucles (el de k por j)
     * 2. Definir las variables de bucle antes y el index también
     */
    double **d = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
        d[i] = (double *)malloc(N * sizeof(double));

    double *e = (double *)malloc(N * sizeof(double));
    double f = 0.0;

    for (int i = 0; i < N; i++) // N iteraciones
    {
        for (int k = 0; k < 8; k++) // 8 iteraciones
        {
            for (int j = 0; j < N; j++) // N iteraciones
            {
                d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]); // 9 accesos
            }
        }
    }
    int index;
    for (int i = 0; i < N; i++)
    {
        index = in.ind[i];          // 1 acceso
        e[i] = d[index][index] / 2; // 3 accesos
        f += e[i];                  // 2 accesos
    }

    for (int i = 0; i < N; i++)
        free(d[i]);
    free(d);
    free(e);

    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial optimizado por orden: f = %4lf\n", f);
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
