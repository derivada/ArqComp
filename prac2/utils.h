#ifndef UTILS_H
#define UTILS_H

#define DEBUG_MSG 0

typedef struct
{
    double **a, **b, *c;
    int *ind;
} datos;

typedef struct
{
    int ciclos;
    double microsegundos;
} tiempos;

// Funciones de inicializacion y liberación de memoria
void inicializacion(datos *in, int N, int semilla);
void inicializacion2(datos *in, int N, int semilla);
void inicializacionAVX(datos *in, int N, int semilla);
void liberarMemoria (datos in, int N);
tiempos medirTiempoEjecucion (void (*funcion)(datos), datos data);
double get_counter();
void start_counter();

#endif // UTILS_H