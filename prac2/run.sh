# Compilamos cada uno de los programas
# create array arr of strings str1 str2 str3

gcc -Wall -O0 -o algSecuencial algSecuencial.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoOrden algSecuencialOptimizadoOrden.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado"
    exit 1
fi

gcc -Wall -O0 -o algSecuencialOptimizadoUnrolling algSecuencialOptimizadoUnrolling.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial optimizado"
    exit 1
fi


if [ -f salidaSec.txt ]
then
    rm salidaSec.txt
fi

if [ -f salidaSecOpt.txt ]
then
    rm salidaSecOpt.txt
fi

echo "N,alg,ck_medios" > salida.txt

# Ejecutamos cada programa 10 veces para cada valor de N
valoresN=(250 500 750 1000 1500 2000 2550 3000)
for i in {1..10}; do
for N in ${valoresN[@]}; do  
    # get random seed
    SEED=$(($RANDOM))
    ./algSecuencial $N $SEED salida.txt          
    ./algSecuencialOptimizadoOrden $N $SEED salida.txt    
    ./algSecuencialOptimizadoUnrolling $N $SEED salida.txt   
done
done

# Ordenar archivo por primera columna y después tercera numericamente
sort -t, -k1,1n -k3,3n salida.txt > salidaOrd.txt

mv salidaOrd.txt salida.txt

# Limpiamos ejecutables
rm algSecuencial algSecuencialOptimizadoOrden algSecuencialOptimizadoUnrolling