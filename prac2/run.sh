# Compilamos cada uno de los programas
# create array arr of strings str1 str2 str3

gcc -Wall -O0 -o algSecuencial_O0.o algSecuencial.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial"
    exit 1
fi
gcc -Wall -O2 -o algSecuencial_O2.o algSecuencial.c utils.c
gcc -Wall -O3 -o algSecuencial_O3.o algSecuencial.c utils.c

gcc -Wall -O0 -o algSecuencialOptimizadoOrden_O0.o algSecuencialOptimizadoOrden.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por orden"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrollingv1_O0.o algSecuencialOptimizadoUnrollingv1.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling v1"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrollingv2_O0.o algSecuencialOptimizadoUnrollingv2.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling v3"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrollingv3_O0.o algSecuencialOptimizadoUnrollingv3.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling v2"
    exit 1
fi
gcc -Wall -O2 -o algSecuencialOptimizadoUnrollingv3_O2.o algSecuencialOptimizadoUnrollingv3.c utils.c
gcc -Wall -O3 -o algSecuencialOptimizadoUnrollingv3_O3.o algSecuencialOptimizadoUnrollingv3.c utils.c

gcc -Wall -O0 -o algSecuencialOptimizadoTiling_O0.o algSecuencialOptimizadoTiling.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por tiling"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoDefinitivo_O0.o algSecuencialOptimizadoDefinitivo.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado definitivo"
    exit 1
fi
gcc -Wall -O0 -o algSecuencialOptOperaciones_O0.o algSecuencialOptOperaciones.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado con reordenamiento de operaciones"
    exit 1
fi

gcc -Wall -O0 -o algAVX2_O0.o algAVX2.c utils.c -mavx2
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de AVX2"
    exit 1
fi

gcc -Wall -O2 -o algAVX2_O2.o algAVX2.c utils.c -mavx2

gcc -Wall -O0 -o algAVX2store_O0.o algAVX2store.c utils.c -mavx2
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de AVX2 con store"
    exit 1
fi
gcc -Wall -O2 -o algAVX2store_O2.o algAVX2.c utils.c -mavx2

gcc -Wall -O0 -o algOMP_O0.o algOMP.c utils.c -fopenmp
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de OMP"
    exit 1
fi

gcc -Wall -O2 -o algOMP_O2.o algOMP.c utils.c -fopenmp
gcc -Wall -O3 -o algOMP_O3.o algOMP.c utils.c -fopenmp

gcc -Wall -O0 -o algAVX2_OMP_O0.o algAVX2_OMP.c utils.c -fopenmp -mavx2
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de AVX2 + OMP"
    exit 1
fi

gcc -Wall -O2 -o algAVX2_OMP_O2.o algAVX2_OMP.c utils.c -fopenmp -mavx2
gcc -Wall -O3 -o algAVX2_OMP_O3.o algAVX2_OMP.c utils.c -fopenmp -mavx

# Reseteamos el archivo de salida
if [ -f salida.txt ]
then
    rm salida.txt
fi
echo "N,alg,ck,ck_medios,t_us" > salida.txt


# Ejecutamos cada programa 10 veces para cada valor de N
valoresN=(250 500 750 1000 1500 2000 2550 3000)

MAX_TESTS=10
count=0
# loop MAX_TESTS times
while [ $count -lt $MAX_TESTS ]; do
    for N in ${valoresN[@]}; do  
        # get random seed
        SEED=$(($RANDOM))
        ./algSecuencial_O0.o $N $SEED salida.txt
        #./algSecuencialOptimizadoDefinitivo_O0.o $N $SEED salida.txt
        #./algSecuencialOptOperaciones_O0.o $N $SEED salida.txt
        #./algSecuencial_O2.o $N $SEED salida.txt
        #./algSecuencial_O3.o $N $SEED salida.txt          
        #./algSecuencialOptimizadoOrden_O0.o $N $SEED salida.txt   
        #./algSecuencialOptimizadoUnrollingv2_O0.o $N $SEED salida.txt
        #./algSecuencialOptimizadoUnrollingv2_O2.o $N $SEED salida.txt
        #./algSecuencialOptimizadoUnrollingv2_O3.o $N $SEED salida.txt   
        ./algSecuencialOptimizadoTiling_O0.o 4 4 $N $SEED salida.txt
        ./algSecuencialOptimizadoTiling_O0.o 16 16 $N $SEED salida.txt
        ./algSecuencialOptimizadoTiling_O0.o 64 64 $N $SEED salida.txt
        ./algSecuencialOptimizadoTiling_O0.o 256 256 $N $SEED salida.txt
        #./algSecuencialOptimizadoTiling_O0.o 8 $N $SEED salida.txt
        #./algSecuencialOptimizadoTiling_O0.o 16 $N $SEED salida.txt   
        #./algAVX2store_O0.o $N $SEED salida.txt
        #./algAVX2store_O2.o $N $SEED salida.txt
        #./algOMP_O0.o 2 $N $SEED salida.txt
        #./algOMP_O0.o 4 $N $SEED salida.txt
        #./algOMP_O2.o 2 $N $SEED salida.txt
        #./algOMP_O2.o 4 $N $SEED salida.txt
        #./algAVX2_OMP_O0.o 2 $N $SEED salida.txt
        #./algAVX2_OMP_O0.o 4 $N $SEED salida.txt
        #./algAVX2_OMP_O2.o 2 $N $SEED salida.txt
        #./algAVX2_OMP_O2.o 4 $N $SEED salida.txt
    done
    (( count++ ))
    echo "Tests done ($count / $MAX_TESTS)"
done

# Ordenamos el archivo de salida por primera columna y después tercera numericamente
sort -t, -k1,1n -k3,3n salida.txt > salidaOrd.txt
mv salidaOrd.txt salida.txt

# Limpiamos todos los ficheros .o
rm *.o