# Compilamos cada uno de los programas
# create array arr of strings str1 str2 str3

gcc -Wall -O0 -o algSecuencial.o algSecuencial.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoOrden.o algSecuencialOptimizadoOrden.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por orden"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrollingv1.o algSecuencialOptimizadoUnrollingv1.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling v1"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrollingv2.o algSecuencialOptimizadoUnrollingv2.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling v2"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoTiling.o algSecuencialOptimizadoTiling.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por tiling"
    exit 1
fi

gcc -Wall -O0 -o algAVX2.o algAVX2.c utils.c -mavx2
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de AVX2"
    exit 1
fi

gcc -Wall -O0 -o algOMP.o algOMP.c utils.c -fopenmp
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo de OMP"
    exit 1
fi

# Reseteamos el archivo de salida
if [ -f salida.txt ]
then
    rm salida.txt
fi
echo "N,alg,ck,ck_medios,t_us" > salida.txt


# Ejecutamos cada programa 10 veces para cada valor de N
valoresN=(32 128 512 2048)
MAX_TESTS=5
count=0
# loop MAX_TESTS times
while [ $count -lt $MAX_TESTS ]; do
    for N in ${valoresN[@]}; do  
        # get random seed
        SEED=$(($RANDOM))
        ./algSecuencial.o $N $SEED salida.txt          
        #./algSecuencialOptimizadoOrden.o $N $SEED salida.txt    
        # ./algSecuencialOptimizadoUnrollingv1.o $N $SEED salida.txt
        ./algSecuencialOptimizadoUnrollingv2.o $N $SEED salida.txt   
        # ./algSecuencialOptimizadoTiling.o 2 $N $SEED salida.txt
        #./algSecuencialOptimizadoTiling.o 4 $N $SEED salida.txt
        # ./algSecuencialOptimizadoTiling.o 8 $N $SEED salida.txt
        # ./algSecuencialOptimizadoTiling.o 16 $N $SEED salida.txt   
        ./algAVX2.o $N $SEED salida.txt
        ./algOMP.o $N $SEED salida.txt
    done
    (( count++ ))
    echo "Tests done ($count / $MAX_TESTS)"
done

# Ordenamos el archivo de salida por primera columna y después tercera numericamente
sort -t, -k1,1n -k3,3n salida.txt > salidaOrd.txt
mv salidaOrd.txt salida.txt

# Limpiamos todos los ficheros .o
rm *.o