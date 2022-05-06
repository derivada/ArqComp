#define UNROLL_SIZE 50
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    for (int i = 1; i < UNROLL_SIZE; i++)
    {
        printf("int j%d = j + %d;\n", i, i);
        printf("e[j%d] = d[in.ind[j%d]][in.ind[j%d]] / 2;\n",
               i, i, i);
        printf("free(d[in.ind[j%d]]);\n", i);
    }
    return 0;
}
