# Primero compilamos con O0 para ejecutar los 2 primeros ejercicios
gcc -Wall -O0 -o main main.c 
if [ $? -ne 0 ]
then
    echo "Error al compilar main.c"
    exit 1
fi

rm salida1.txt salida2.txt
echo "N,ck,ck_medios" > salida1.txt
echo "N,ck,ck_medios" > salida2.txt

valoresN=(250 500 750 1000 1500 2000 2550 3000)
for i in {1..10}; do
for N in ${valoresN[@]}; do  
    ./main $N 1 salida1.txt # Algoritmo secuencial
    ./main $N 2 salida2.txt # Algoritmo secuencial optimizado
done
done

# order file by first column numerically
sort -n -k 1 salida1.txt > salida1_order.txt
sort -n -k 1 salida2.txt > salida2_order.txt
rm salida1.txt salida2.txt

rm main