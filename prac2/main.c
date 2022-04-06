#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG_MSG 0

void start_counter();
double get_counter();
double mhz();
void shuffle(int A[], int n);

FILE *outputFile;

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

typedef struct
{
    double **a, **b, *c, **d, *e, f;
    int *ind;
} datos;

typedef struct
{
    int ck;
    double ck_medios;
} tiempos;

// Funciones de inicializacion y liberación de memoria
void inicializacion(datos *in);
void freeMyNiggaJerome(datos in);
void cerrarArchivoSalida(int status, void *args);

// Funciones de algoritmos
tiempos algoritmoSecuencial(datos in);
tiempos algoritmoSecuencialOptimizado(datos in);

// Variables del experimento
int N, ALG;
void leerParametros(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    leerParametros(argc, argv);
    datos *casoPrueba = (datos *)malloc(sizeof(datos));
    tiempos results;

    inicializacion(casoPrueba);

    // Ordenamos el vector ind de forma aleatoria
    shuffle(casoPrueba->ind, N);

    switch (ALG)
    {
    case 1:
        if (DEBUG_MSG)
            printf("Ejecutando algoritmo secuencial!\n");
        results = algoritmoSecuencial(*casoPrueba);
        break;
    case 2:
        if (DEBUG_MSG)

            printf("Ejecutando algoritmo secuencial optimizado!\n");
        results = algoritmoSecuencialOptimizado(*casoPrueba);
        break;
    case 3:
    case 4:
    default:
        printf("Algoritmo no encontrado!");
        exit(EXIT_FAILURE);
    }

    // Imprimimos los resultados
    if (DEBUG_MSG)

        printf("Tiempos: ck = %d\tck_medio = %4lf\n", results.ck, results.ck_medios);

    // Registramos los resultados
    fprintf(outputFile, "%d,%d,%lf\n", N, results.ck, results.ck_medios);

    // Liberación de mi negro jerónimo
    freeMyNiggaJerome(*casoPrueba);
    exit(EXIT_SUCCESS);
}

void leerParametros(int argc, const char *argv[])
{
    if (argc != 4)
    {
        printf("Uso correcto: ./main N ALG OUTPUT_FILE\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // N: tamaño de la operación
        N = atoi(argv[1]);
        // ALG: Algoritmo a usar
        ALG = atoi(argv[2]);
        if ((outputFile = fopen(argv[3], "a")) == NULL)
        {
            printf("Error al abrir el archivo de salida\n");
            exit(EXIT_FAILURE);
        }
        on_exit(cerrarArchivoSalida, NULL);
        if (N <= 0 || ALG <= 0) // Comprobamos que los valores de entrada son válidos
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

void freeMyNiggaJerome(datos in)
{
    for (int i = 0; i < N; i++)
    {
        free(in.a[i]);
        free(in.d[i]);
        if (i < 8)
            free(in.b[i]);
    }
    free(in.a);
    free(in.b);
    free(in.c);
    free(in.d);
    free(in.e);
    free(in.ind);
}

void inicializacion(datos *in)
{
    in->a = (double **)malloc(N * sizeof(double *));
    in->b = (double **)malloc(8 * sizeof(double *));
    in->c = (double *)malloc(8 * sizeof(double));
    in->d = (double **)malloc(N * sizeof(double *));
    in->e = (double *)malloc(N * sizeof(double));
    in->ind = (int *)malloc(N * sizeof(int));
    tiempos results;
    for (int i = 0; i < N; i++)
    {
        in->a[i] = (double *)malloc(sizeof(double) * 8);
        if (i < 8)
        {
            in->b[i] = (double *)malloc(sizeof(double) * N);
        }
        (in->d)[i] = (double *)malloc(sizeof(double) * N);
        memset(in->d[i], 0, N * sizeof(double));
    }

    memset(in->e, 0, N * sizeof(double));
    in->f = 0;

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
}

void shuffle(int A[], int n)
{
    for (int i = n - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
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
    if (result < 0)
    {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

tiempos algoritmoSecuencial(datos in)
{
    tiempos results;
    // accesos = (9*8*N*N) + (N*5*2) = N*(72*N + 10)
    int accesos = N * (72 * N + 10);
    // Inicializamos el contador
    start_counter();
    for (int i = 0; i < N; i++)                                        // N iteraciones
        for (int j = 0; j < N; j++)                                    // N iteraciones
            for (int k = 0; k < 8; k++)                                // 8 iteraciones
                in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]); // 9 accesos

    for (int i = 0; i < N; i++)
    {                                             // N iteraciones
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2; // 5 accesos
        in.f += in.e[i];                          // 2 accesos
    }

    // Obtenemos los resultados temporales
    results.ck = get_counter();
    results.ck_medios = ((double)results.ck / accesos);
    if (DEBUG_MSG)
        printf("Resultado del algoritmo secuencial: f = %4lf\n", in.f);
    return results;
}

tiempos algoritmoSecuencialOptimizado(datos in)
{
    tiempos results;
    // accesos = (9*8*N*N) + (N*5*2) = N*(72*N + 10)
    int accesos = N * (72 * N + 10);
    // Inicializamos el contador
    start_counter();
    for (int i = 0; i < N; i++)                                        // N iteraciones
        for (int j = 0; j < N; j++)                                    // N iteraciones
            for (int k = 0; k < 8; k++)                                // 8 iteraciones
                in.d[i][j] += 2 * in.a[i][k] * (in.b[k][j] - in.c[k]); // 9 accesos

    for (int i = 0; i < N; i++)
    {                                             // N iteraciones
        in.e[i] = in.d[in.ind[i]][in.ind[i]] / 2; // 5 accesos
        in.f += in.e[i];                          // 2 accesos
    }

    // Obtenemos los resultados temporales
    results.ck = get_counter();
    results.ck_medios = ((double)results.ck / accesos);
    if(DEBUG_MSG)
        printf("Resultado del algoritmo secuencial: f = %4lf\n", in.f);
    return results;
}