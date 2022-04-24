#ifndef UTILS_H
#define UTILS_H

#define DEBUG_MSG 1

typedef struct
{
    double **a, **b, *c, **d, *e, f;
    int *ind;
} datos;

typedef struct
{
    int ck;
    int accesos;
    double ck_medios;
} tiempos;

// Funciones de inicializacion y liberación de memoria
void inicializacion (datos *in, int N, int semilla);
void freeMyNiggaJerome (datos in, int N);
tiempos medirTiempoEjecucion (int (*funcion)(datos), datos data);
double get_counter();
void start_counter();

#endif // UTILS_H