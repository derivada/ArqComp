#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>
#include "utils.h"

#define ALG_NAME "AVX2"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
void algoritmoAVX2(datos in);

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
    inicializacionAVX(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algoritmoAVX2, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (%s),%d,%lf\n",
            N, ALG_NAME, optimizationFlag, results.ciclos, results.microsegundos);

    // Liberación de mi negro jerónimo
    liberarMemoria(*casoPrueba, N);
    exit(EXIT_SUCCESS);
}

void cargarB(datos in)
{
    double *aux = (double *)malloc(N * 8 * sizeof(double));
    for (int i = 0; i < 8; i++)
    {
        in.b[i] = aux + N * sizeof(double);
    }
}

void algoritmoAVX2(datos in)
{
    int newN = N;
    if (newN % 4 != 0)
        newN = newN + (4 - N % 4);

    double **d = (double **)malloc(N * sizeof(double *));
    double *e = (double *)aligned_alloc(32, sizeof(double) * newN);
    double f = 0.0;

    __m256d scalar2 = _mm256_set1_pd(2);
    __m256d c0 = _mm256_load_pd(&in.c[0]);
    __m256d c4 = _mm256_load_pd(&in.c[4]);

    for (int i = 0; i < N; i++)
    {
        d[i] = (double *)aligned_alloc(32, sizeof(double) * newN);
        __m256d a0 = _mm256_mul_pd(_mm256_load_pd(&in.a[i][0]), scalar2);
        __m256d a4 = _mm256_mul_pd(_mm256_load_pd(&in.a[i][4]), scalar2);
        int j = 0, nextJ = 1;
        for (; j < newN; j += 2, nextJ += 2)
        {
            __m256d sum_j01 = _mm256_hadd_pd(_mm256_add_pd(
                                                 _mm256_mul_pd(a0, _mm256_sub_pd(_mm256_set_pd(in.b[3][j], in.b[2][j], in.b[1][j], in.b[0][j]), c0)),
                                                 _mm256_mul_pd(a4, _mm256_sub_pd(_mm256_set_pd(in.b[7][j], in.b[6][j], in.b[5][j], in.b[4][j]), c4))),
                                             _mm256_add_pd(
                                                 _mm256_mul_pd(a0, _mm256_sub_pd(_mm256_set_pd(in.b[3][nextJ], in.b[2][nextJ], in.b[1][nextJ], in.b[0][nextJ]), c0)),
                                                 _mm256_mul_pd(a4, _mm256_sub_pd(_mm256_set_pd(in.b[7][nextJ], in.b[6][nextJ], in.b[5][nextJ], in.b[4][nextJ]), c4))));
            _mm_stream_pd(&d[i][j], _mm_add_pd(_mm256_extractf128_pd(sum_j01, 0), _mm256_extractf128_pd(sum_j01, 1)));
            j += 2, nextJ += 2;
            __m256d sum_j23 = _mm256_hadd_pd(_mm256_add_pd(
                                                 _mm256_mul_pd(a0, _mm256_sub_pd(_mm256_set_pd(in.b[3][j], in.b[2][j], in.b[1][j], in.b[0][j]), c0)),
                                                 _mm256_mul_pd(a4, _mm256_sub_pd(_mm256_set_pd(in.b[7][j], in.b[6][j], in.b[5][j], in.b[4][j]), c4))),
                                             _mm256_add_pd(
                                                 _mm256_mul_pd(a0, _mm256_sub_pd(_mm256_set_pd(in.b[3][nextJ], in.b[2][nextJ], in.b[1][nextJ], in.b[0][nextJ]), c0)),
                                                 _mm256_mul_pd(a4, _mm256_sub_pd(_mm256_set_pd(in.b[7][nextJ], in.b[6][nextJ], in.b[5][nextJ], in.b[4][nextJ]), c4))));
            _mm_stream_pd(&d[i][j], _mm_add_pd(_mm256_extractf128_pd(sum_j23, 0), _mm256_extractf128_pd(sum_j23, 1)));
        }
    }

    for (int i = 0; i < N; i++)
    {
        int index = in.ind[i];
        e[i] = d[index][index] / 2;
        free(d[index]);
        f += e[i];
    }
    free(d);
    free(e);
    
    if (DEBUG_MSG)
    {
        if (DEBUG_MSG > 1)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N - 1; j++)
                {
                    printf("%4lf, ", d[i][j]);
                }
                printf("%4lf\n", d[i][N - 1]);
            }
        }
        printf("Resultado del algoritmo avx: f = %4lf\n", f);
    }
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
