/**
 * @author Pablo Landrove (@PabloLandro)
 * @author Pablo Díaz (@derivada)
 * @brief Práctica 1 Arquitectura de Computadores
 * @date 2022-02-16
 *
 * NOTA: Compilar con las flags -O0 y -msse3
 */

/*
 *  Info relevante del procesador (ordenador de Pablo Díaz)
 *  Intel Core i5-8300H @ 2.30GHz (4 cores)
 *
 *  Cache nivel 1 (datos) 4x32KB (128KB), 8-way-set-associative, 64 sets
 *  Cache nivel 1 (instrucciones) 4x32KB (128KB), 8-way-set-associative, 64 sets
 *  Cache nivel 2 (unificada) 4x256KB (1024KB), 4-way-set-associative, 1024 sets
 *  Cache nivel 3 (unificada) 4x8192KB (32768KB), 16-way-set-associative, 8192 sets
 */

void start_counter();
double get_counter();
double mhz();

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

// gcc main.c rutinas_clock.c -o main -O0 -msse3

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pmmintrin.h>
#include <ctype.h>
#include <wait.h>
#include <unistd.h>
#include <math.h>

// Constantes del CPU
int CLS, S1, S2;

// Parametros del test
int D, L, R; 

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        printf("Uso correcto ./main D L CLS S1 S2");
        exit(EXIT_FAILURE);
    }
    else
    {
        // D: Salto entre elementos
        D = atoi(argv[1]);
        // L: Número de lineas cache a usar
        L = atoi(argv[2]);
        // CLS: Tamaño de línea en bytes
        CLS = atoi(argv[3]);
        // S1: Número de líneas en la L1
        S1 = atoi(argv[4]);
        // S2: Número de líneas en la L2
        S2 = atoi(argv[5]);
        // Hallar R: numero de elem a sumar
        if (D <= 0 || L <= 0 || CLS <= 0 || S1 <= 0 || S2 <= 0)
        {
            printf("Alguno de los argumentos es incorrecto\n");
            exit(EXIT_FAILURE);
        }

        // Calcular R usando la formula
        R = (int) ceil((double)(L * CLS) / (double)(D * sizeof(double)));
    }

    double *A, S[10];
    int ind[R];
    double ck, ck_medio;
    int accesos = 10 * R;

    // Reserva de memoria para el vector A
    A = (double *)_mm_malloc(R * D * sizeof(double), CLS);

    // Inicializamos el vector ind y los números aleatorios de A
    srand(time(NULL));

    for (int i = 0; i < R; i++)
    {
        ind[i] = i * D;
        A[ind[i]] = (((double)rand() / RAND_MAX) + 1.0); // double en rango [1,2)
        if (rand() / RAND_MAX < 0.5)
        {
            A[ind[i]] = -A[ind[i]]; // signo aleatorio
        }
    }

    start_counter();

    // Repetimos la reducción 10 veces
    for (int i = 0; i < 10; i++)
    {
        S[i] = 0;
        for (int j = 0; j < R; j++)
        {
            S[i] += A[ind[j]];
        }
    }

    // Obtenemos los resultados temporales
    ck = get_counter();
    ck_medio = (double)(ck / accesos);
    
    // Imprimimos datos y resultados
    printf("Argumentos del test:\n");
    printf("\tNúmero de elementos consultados: R = %d\n", R);
    printf("\tSalto entre elementos consultados: D = %d (%ld bytes)\n", D, (D*sizeof(double)));
    printf("\tNúmero de líneas accedidas: L = %d\n", L);
    printf("\nPropiedades del ordenador:\n");
    printf("\tTamaño de línea: CLS = %d\n", CLS);
    printf("\tNúmero de líneas en caché nivel 1: S1 = %d\n", S1);
    printf("\tNúmero de líneas en caché nivel 2: S2 = %d\n", S2);
    printf("\nTiempos y ciclos:\n");
    printf("\tCiclos de ejecución totales = %1.10lf\n", ck);
    printf("\tTiempo medio de acceso = %1.10lf ciclos\n", ck_medio);

    // Imprimimos el vector S
    printf("\nVector de resultados:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("\tS[%d]: %lf\n", i, S[i]);
    }
    
    _mm_free(A);

    printf("\nMemoria liberada y programa terminado con éxito!\n");
    return EXIT_SUCCESS;
}

/**
 * Funciones para medir tiempos de la librería aportada en el CV
 * rutinas_clock.c
 */

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
void start_counter()
{
    access_counter(&cyc_hi, &cyc_lo);
}

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
    if (result < 0)
    {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}