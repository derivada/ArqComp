# Compilamos cada uno de los programas
gcc -Wall -O0 -o algSec algSecuencial.c utils.c
if [ $? -ne 0 ]
then
    echo "Error al compilar algoritmo secuencial"
    exit 1
fi

gcc -Wall -O0 -o algSecOpt algSecuencialOptimizado.c utils.c
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

echo "N,ck,ck_medios" > salidaSec.txt
echo "N,ck,ck_medios" > salidaSecOpt.txt

# Ejecutamos cada programa 10 veces para cada valor de N
valoresN=(250 500 750 1000 1500 2000 2550 3000)
for i in {1..1}; do
for N in ${valoresN[@]}; do  
    # get random seed
    SEED=$(($RANDOM))
    ./algSec $N $SEED salidaSec.txt          # Algoritmo secuencial
    ./algSecOpt $N $SEED salidaSecOpt.txt    # Algoritmo secuencial optimizado
done
done

# Ordenar archivo por primera columna numericamente
sort -n -k 1 salidaSec.txt > salidaSec_order.txt
sort -n -k 1 salidaSecOpt.txt > salidaSecOpt_order.txt
mv salidaSec_order.txt salidaSec.txt
mv salidaSecOpt_order.txt salidaSecOpt.txt

# Limpiamos ejecutables
rm algSec algSecOpt