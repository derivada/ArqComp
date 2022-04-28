#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>
#include "utils.h"

#define ALG_NAME "algAVX2"
FILE *outputFile;

// Funciones de leer parámetros y cerrar archivo de salida
void leerParametros(int argc, const char *argv[]);
void cerrarArchivoSalida(int status, void *args);

// Algoritmo a usar
int algoritmoAVX2(datos in);

// Variables del experimento
int N, semilla;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    if (N % 4)
    {
        printf("ERROR EN AVX: No implementado aún para N no divisible entre 4\n");
        exit(EXIT_FAILURE);
    }

    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    // Inicializamos y aleatoriazamos el caso de prueba
    inicializacionAVX(casoPrueba, N, semilla);

    // Ejecutamos el algoritmo midiendo tiempo
    results = medirTiempoEjecucion(algoritmoAVX2, *casoPrueba);

    // Registramos los resultados
    fprintf(outputFile, "%d,%s,%d,%lf,%lf\n", N, ALG_NAME, results.ck, results.ck_medios, results.microsegundos);

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

int algoritmoAVX2(datos in)
{
    __m256d scalar2 = _mm256_set1_pd(2);
    __m256d c0 = _mm256_load_pd(&in.c[0]);
    __m256d c4 = _mm256_load_pd(&in.c[4]);
    for (int i = 0; i < N; i++)
    {
        // in.a[i][k] * 2
        __m256d a0 = _mm256_load_pd(&in.a[i][0]);
        __m256d a4 = _mm256_load_pd(&in.a[i][4]);
        a0 = _mm256_mul_pd(a0, scalar2);
        a4 = _mm256_mul_pd(a4, scalar2);
        for (int j = 0; j < N / 4; j += 4)
        {
            int a = j + 1;
            int b = j + 2;
            int c = j + 3;
            __m256d b0 = _mm256_set_pd(in.b[3][j], in.b[2][j], in.b[1][j], in.b[0][j]);
            __m256d b4 = _mm256_set_pd(in.b[7][j], in.b[6][j], in.b[5][j], in.b[4][j]);

            // in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]);
            __m256d d = _mm256_add_pd(
                _mm256_mul_pd(a0, _mm256_sub_pd(b0, c0)),
                _mm256_mul_pd(a4, _mm256_sub_pd(b4, c4)));

            // Reducción y guardado en d
            __m256d sum = _mm256_hadd_pd(d, d);
            __m128d sum_high = _mm256_extractf128_pd(sum, 1);
            __m128d result = _mm_add_pd(sum_high, _mm256_castpd256_pd128(sum));
            in.d[i][j] = ((double *)&result)[0];
        }
    }

    for (int i = 0; i < N; i++)
    {
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2;
        in.f += in.e[i];
    }

    if (DEBUG_MSG)
        printf("Resultado del algoritmo optimizado con AVX: f = %4lf\n", in.f);

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
