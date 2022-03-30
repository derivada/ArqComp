#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void start_counter();
double get_counter();
double mhz();
void shuffle(int A[], int n);

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

typedef struct {
    double **a, **b, *c, **d, *e, f;
    int *ind;
} datos;

typedef struct {
    int ck;
    double ck_medios;
} tiempos;

// Variables del experimento
int N, ALG;
void leerParametros(int argc, const char *argv[]);

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    leerParametros(argc, argv);
    datos casoPrueba;
    int accesos = 0;
    double ck, ck_medio;

    inicializacion(casoPrueba);

    // Ordenamos el vector ind de forma aleatoria
    shuffle(casoPrueba.ind, N);


    switch (ALG) {
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        printf("Algoritmo no encontrado!");
        exit(EXIT_FAILURE);
    }
    /*
    // Inicializamos el contador
    start_counter();
    // Obtenemos los resultados temporales
    ck = get_counter();
    ck_medio = (double)(ck / accesos);
    */

    // Imprimimos los resultados
    printf("f = %4lf\tck = %4lf\tck_medio = %4lf\n", f, ck, ck_medio);

    // Liberación de mi negro jerónimo
    freeMyNiggaJerome(casoPrueba);
    exit(EXIT_SUCCESS);
}

void leerParametros(int argc, const char *argv[]) {
    if (argc <= 3) {
        printf("Uso correcto: ./main N ALG\n");
        exit(EXIT_FAILURE);
    } else {
        // N: tamaño de la operación
        N = atoi(argv[1]);
        // ALG: Algoritmo a usar
        ALG = atoi(argv[2]);
        if (N <= 0 ||
            ALG <= 0) // Comprobamos que los valores de entrada son válidos
        {
            printf("Alguno de los argumentos numéricos es incorrecto\n");
            exit(EXIT_FAILURE);
        }
    }
}

void freeMyNiggaJerome(datos in) {
    for (int i = 0; i < N; i++) {
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

void inicializacion(datos in) {
    in.a = (double **)malloc(N * sizeof(double *));
    in.b = (double **)malloc(8 * sizeof(double *));
    in.c = (double *)malloc(8 * sizeof(double));
    in.d = (double **)malloc(N * sizeof(double *));
    in.e = (double *)malloc(N * sizeof(double));
    in.ind = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        in.a[i] = (double *)malloc(sizeof(double) * 8);
        if (i < 8) {
            in.b[i] = (double *)malloc(sizeof(double) * N);
        }
        in.d[i] = (double *)malloc(sizeof(double) * N);
        memset(in.d[i], 0, N * sizeof(double));
    }
    memset(in.e, 0, N * sizeof(double));
    in.f = 0;

    for (int i = 0; i < N; i++) {
        in.ind[i] = i;
        in.c[i] = (double)rand() / RAND_MAX * 2.0 -
                  1.0; // Double en el rango (-1.0, 1.0)
        for (int j = 0; j < 8; j++) {
            in.a[j][i] = (double)rand() / RAND_MAX * 2.0 -
                         1.0; // Double en el rango (-1.0, 1.0)
            in.b[i][j] = (double)rand() / RAND_MAX * 2.0 -
                         1.0; // Double en el rango (-1.0, 1.0)
        }
    }
}

void shuffle(int A[], int n) {
    for (int i = n - 1; i >= 1; i--) {
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
void access_counter(unsigned *hi, unsigned *lo) {
    asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
        : "=r"(*hi), "=r"(*lo)                /* and move results to */
        : /* No input */                      /* the two outputs */
        : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter() { access_counter(&cyc_hi, &cyc_lo); }

/* Return the number of cycles since the last call to start_counter. */
double get_counter() {
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
    if (result < 0) {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

tiempos algoritmoSecuencial(datos in) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 8; k++) {
                in.d[i][j] += 2 * in.[i][k] * (in.b[k][j] - in.c[k]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        e[i] = d[ind[i]][ind[i]] / 2;
        f += e[i];
    }
}