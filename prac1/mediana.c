/**
 * @author Pablo Landrove (@PabloLandro)
 * @author Pablo Díaz (@derivada)
 * @brief Práctica 1 Arquitectura de Computadores
 * @date 2022-02-16
 *
 * NOTA: Compilar con las flags -O0 y -msse3
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void insertionSortInt(int array[], int size);
void insertionSortDouble(double array[], int size);

int main(int argc, char **argv)
{
    FILE *datos, *result;
    size_t size = 100;
    char *line = malloc(size * sizeof(char));
    double ck_medios[35][10];
    int cks[35][10];
    int pts[35][3];
    char *filename = (char *)malloc(100 * sizeof(char));

    for (int i = 1; i <= 10; i++)
    {
        sprintf(filename, "results%d.csv", i);
        if ((datos = fopen(filename, "r")) == NULL)
        {
            perror("Error al abrir el archivo");
            exit(EXIT_FAILURE);
        }
        int j = 0;
        getline(&line, &size, datos);
        while (getline(&line, &size, datos))
        {
            //printf("LINE: %s\n", line);
            char *tok;
            tok = strtok(line, ",");
            pts[j][0] = atoi(tok);
            tok = strtok(NULL, ",");
            pts[j][1] = atoi(tok);
            tok = strtok(NULL, ",");
            pts[j][2] = atoi(tok);
            tok = strtok(NULL, ",");
            cks[j][i - 1] = atoi(tok);
            tok = strtok(NULL, ",");
            ck_medios[j][i - 1] = strtod(tok, NULL);
            j++;
            if (j >= 35)
                break;
        }
        fclose(datos);
    }

    result = fopen("results.csv", "w");
    fprintf(result, "D,R,L,ck,ck_medio\n");

    for (int j = 0; j < 35; j++)
    {
        insertionSortInt(cks[j], 10);
        insertionSortDouble(ck_medios[j], 10);
        int ck_mediana = (cks[j][4] + cks[j][5]) / 2;
        double ck_medios_mediana = (ck_medios[j][4] + ck_medios[j][5]) / 2;
        fprintf(result, "%d,%d,%d,%d,%lf\n", pts[j][0], pts[j][1], pts[j][2], ck_mediana, ck_medios_mediana);
    }

    fclose(result);
    exit(EXIT_SUCCESS);
}

void insertionSortInt(int array[], int size)
{
    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        // Compare key with each element on the left of it until an element smaller than
        // it is found.
        // For descending order, change key<array[j] to key>array[j].
        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

void insertionSortDouble(double array[], int size)
{
    for (int step = 1; step < size; step++)
    {
        double key = array[step];
        int j = step - 1;

        // Compare key with each element on the left of it until an element smaller than
        // it is found.
        // For descending order, change key<array[j] to key>array[j].
        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}