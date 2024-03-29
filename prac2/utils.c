#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

struct timespec start, stop;

tiempos medirTiempoEjecucion(void (*funcion)(datos), datos data)
{
    tiempos tiempos;
    start_counter();
    clock_gettime(CLOCK_REALTIME, &start);
    (*funcion)(data);
    tiempos.ciclos = get_counter();
    clock_gettime(CLOCK_REALTIME, &stop);
    tiempos.microsegundos = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
    return tiempos;
}

void inicializacion(datos *in, int N, int semilla)
{
    srand(semilla);
    in->a = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
        in->a[i] = (double *)malloc(sizeof(double) * 8);
    in->b = (double **)malloc(8 * sizeof(double *));
    for (int i = 0; i < 8; i++)
        in->b[i] = (double *)malloc(sizeof(double) * N);
    in->c = (double *)malloc(8 * sizeof(double));
    in->ind = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        in->ind[i] = i;
        if (i < 8)
            in->c[i] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
        for (int j = 0; j < 8; j++)
        {
            in->a[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
            in->b[j][i] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
        }
    }
    // Shuffle
    for (int i = N - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        double temp = *(in->a[i]);
        *(in->a[i]) = *(in->a[j]);
        *(in->a[j]) = temp;
    }
}

void inicializacionAVX(datos *in, int N, int semilla)
{
    srand(semilla);
    int innerN = N;
    if (N % 4 != 0)
    {
        N = N + (4 - N % 4);
    }

    in->a = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
        in->a[i] = (double *)aligned_alloc(32, sizeof(double) * 8);
    in->b = (double **)malloc(8 * sizeof(double *));
    for (int i = 0; i < 8; i++)
        in->b[i] = (double *)aligned_alloc(32, sizeof(double) * N);
    in->c = (double *)aligned_alloc(32, 8 * sizeof(double));
    in->ind = (int *)aligned_alloc(32, N * sizeof(int));

    for (int i = 0; i < innerN; i++)
    {
        in->ind[i] = i;
        if (i < 8)
            in->c[i] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
        for (int j = 0; j < 8; j++)
        {
            in->a[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
            in->b[j][i] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Double en el rango (-1.0, 1.0)
        }
    }
    // Shuffle
    for (int i = innerN - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        double temp = *(in->a[i]);
        *(in->a[i]) = *(in->a[j]);
        *(in->a[j]) = temp;
    }
}

void liberarMemoria(datos in, int N)
{
    for (int i = 0; i < N; i++)
    {
        free(in.a[i]);
        if (i < 8)
            free(in.b[i]);
    }
    free(in.a);
    free(in.b);
    free(in.c);
    free(in.ind);
}

/**
 * Funciones para medir tiempos de la librería aportada en el CV
 * rutinas_clock.c
 */

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

/* Set *hi and *lo to the high and low order bits of the cycle counter.
Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo)
{
    asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
        : "=r"(*hi), "=r"(*lo)                /* and move results to */
        : /* No input */                      /* the two outputs */
        : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter() { access_counter(&cyc_hi, &cyc_lo); }

/* Return the number of cycles since the last call to start_counter. */
double get_counter()
{
    unsigned ncyc_hi, ncyc_lo;
    unsigned hi, lo, borrow;
    double result;

    /* Get cycle counter */
    access_counter(&ncyc_hi, &ncyc_lo);

    /* Do double precision subtraction */
    lo = ncyc_lo - cyc_lo;
    borrow = lo > ncyc_lo;
    hi = ncyc_hi - cyc_hi - borrow;
    result = (double)hi * (1 << 30) * 4 + lo;
    return result;
}