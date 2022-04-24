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

gcc -Wall -O0 -o algSecuencialOptimizadoUnrolling.o algSecuencialOptimizadoUnrolling.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por unrolling"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoTiling.o algSecuencialOptimizadoTiling.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado por tiling"
    exit 1
fi

# Reseteamos el archivo de salida
if [ -f salida.txt ]
then
    rm salida.txt
fi
echo "N,alg,ck_medios" > salida.txt


# Ejecutamos cada programa 10 veces para cada valor de N
valoresN=(250 500 750 1000 1500 2000 2550 3000)
for i in {1..1}; do
for N in ${valoresN[@]}; do  
    # get random seed
    SEED=$(($RANDOM))
    ./algSecuencial.o $N $SEED salida.txt          
    ./algSecuencialOptimizadoOrden.o $N $SEED salida.txt    
    ./algSecuencialOptimizadoUnrolling.o $N $SEED salida.txt   
    ./algSecuencialOptimizadoTiling.o $N $SEED salida.txt   
done
done

# Ordenamos el archivo de salida por primera columna y después tercera numericamente
sort -t, -k1,1n -k3,3n salida.txt > salidaOrd.txt
mv salidaOrd.txt salida.txt

# Limpiamos todos los ficheros .o
rm *.o