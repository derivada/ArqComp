#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>
#include <omp.h>
#include "utils.h"

#define ALG_NAME "AVX2+OMP"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algoritmoAVX2_OMP(datos in);

// Variables del experimento
int N, semilla, numThreads;
char *optimizationFlag;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    omp_set_num_threads(numThreads);

    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    // Inicializamos y aleatoriazamos el caso de prueba
    inicializacionAVX(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algoritmoAVX2_OMP, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s (%d threads) (%s),%d,%lf,%lf\n",
            N, ALG_NAME, numThreads, optimizationFlag, results.ck, results.ck_medios, results.microsegundos);

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

int algoritmoAVX2_OMP(datos in)
{
    __m256d scalar2 = _mm256_set1_pd(2);
    __m256d c0 = _mm256_load_pd(&in.c[0]);
    __m256d c4 = _mm256_load_pd(&in.c[4]);
    // bordes
    int newN = N;
    if (N % 4 != 0)
    {
        newN = N + (4 - N % 4);
    }
#pragma omp parallel for
    for (int i = 0; i < newN; i++)
    {
        // in.a[i][k] * 2
        __m256d a0 = _mm256_load_pd(&in.a[i][0]);
        __m256d a4 = _mm256_load_pd(&in.a[i][4]);
        a0 = _mm256_mul_pd(a0, scalar2);
        a4 = _mm256_mul_pd(a4, scalar2);
        int j;
        for (j = 0; j < newN; j += 4)
        {
            // in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]);
            __m256d b0_j0 = _mm256_set_pd(in.b[3][j], in.b[2][j], in.b[1][j], in.b[0][j]);
            __m256d b4_j0 = _mm256_set_pd(in.b[7][j], in.b[6][j], in.b[5][j], in.b[4][j]);
            __m256d d_j0 = _mm256_add_pd(
                _mm256_mul_pd(a0, _mm256_sub_pd(b0_j0, c0)),
                _mm256_mul_pd(a4, _mm256_sub_pd(b4_j0, c4)));

            int a = j + 1;
            __m256d b0_j1 = _mm256_set_pd(in.b[3][a], in.b[2][a], in.b[1][a], in.b[0][a]);
            __m256d b4_j1 = _mm256_set_pd(in.b[7][a], in.b[6][a], in.b[5][a], in.b[4][a]);
            __m256d d_j1 = _mm256_add_pd(
                _mm256_mul_pd(a0, _mm256_sub_pd(b0_j1, c0)),
                _mm256_mul_pd(a4, _mm256_sub_pd(b4_j1, c4)));

            // Reducción y guardado en d
            __m256d sum_j01 = _mm256_hadd_pd(d_j0, d_j1);
            __m128d result_j01 = _mm_add_pd(_mm256_extractf128_pd(sum_j01, 0), _mm256_extractf128_pd(sum_j01, 1));
            in.d[i][j] = ((double *)&result_j01)[0];
            in.d[i][a] = ((double *)&result_j01)[1];

            // UNROLLING DE 4
            int b = j + 2;
            __m256d b0_j2 = _mm256_set_pd(in.b[3][b], in.b[2][b], in.b[1][b], in.b[0][b]);
            __m256d b4_j2 = _mm256_set_pd(in.b[7][b], in.b[6][b], in.b[5][b], in.b[4][b]);
            __m256d d_j2 = _mm256_add_pd(
                _mm256_mul_pd(a0, _mm256_sub_pd(b0_j2, c0)),
                _mm256_mul_pd(a4, _mm256_sub_pd(b4_j2, c4)));

            int c = j + 3;
            __m256d b0_j3 = _mm256_set_pd(in.b[3][c], in.b[2][c], in.b[1][c], in.b[0][c]);
            __m256d b4_j3 = _mm256_set_pd(in.b[7][c], in.b[6][c], in.b[5][c], in.b[4][c]);
            __m256d d_j3 = _mm256_add_pd(
                _mm256_mul_pd(a0, _mm256_sub_pd(b0_j3, c0)),
                _mm256_mul_pd(a4, _mm256_sub_pd(b4_j3, c4)));

            // Reducción y guardado en d
            __m256d sum_j23 = _mm256_hadd_pd(d_j2, d_j3);
            __m128d result_j23 = _mm_add_pd(_mm256_extractf128_pd(sum_j23, 0), _mm256_extractf128_pd(sum_j23, 1));
            in.d[i][b] = ((double *)&result_j23)[0];
            in.d[i][c] = ((double *)&result_j23)[1];
        }
    }

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2;
#pragma omp atomic
        in.f += in.e[i];
    }

    if (DEBUG_MSG)
        printf("Resultado del algoritmo optimizado con OpenMP + AVX: f = %4lf\n", in.f);

    // accesos = (9*8*N*N) + (N*5*2)    // Inicializamos el contador
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
        optimizationFlag = (char *)malloc(3 * sizeof(char));
        strncpy(optimizationFlag, argv[0] + (strlen(argv[0]) - 4), 2);
        *(optimizationFlag + 2) = '\0';
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
