#include <stdio.h>
#include <stdlib.h>

#define N 5

double a[N][8];
double b[8][N];
double c[8];
int ind[N];
dof: variable de salida tipo double

int main (int argc, const char *argv[]) {
    d[N][N]=0; // inicialización de todas las componentes de d a cero;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = 0;
        }
    }

    for (i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            for (k=0; k<8; k++) {
                d[i][j] += 2 * a[i][k] * ( b[k][j]- c[k]);
            }
        }
        f=0;
        for (i=0;i<N;i++){
            e[i]= d[ind[i]][ind[i]]/2;
            f+=e[i];
        }
    }
    Imprimir el valor de f
}