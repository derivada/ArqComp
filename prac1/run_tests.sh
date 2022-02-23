# Script para ejecutar el

# Constantes del experimento
S1=512  # Total líneas cache en la L1
S2=4096 # Total líneas cache en la L2
CLS=64  # Tamaño de la línea caché en bytes

# Tomar  medidas  de  ciclos  para  los  siguientes  valores  de  
# L:  0.5*S1,  1.5*S1,  0.5*S2,  0.75*S2,  2*S2, 4*S2,  8*S2,  
# siendo  S1  el  número  de  líneas  caché  que  caben en  la  caché L1  de  datos  y  S2  el  número  de  líneas  caché que caben en la caché L2.
valoresD=(2 8 16 64 100) # 5 Valores de D elegidos entre 1 y 100

# Compilar el programa con las flags necesarias
gcc -o main main.c -O0 -msse3 -Wall -pedantic 2> compl_errors.txt

# Crear el directorio de logs para las salidas del programa o limpiarlo 
if ! test -d "./logs"
then
    mkdir "./logs"
else
    rm ./logs/log*
fi
# Ejecuta el programa para todos las combinaciones de D y R y lo guarda el archivo logs/log_D_R
for D in "${valoresD[@]}";
do
    R=$(echo "0.5*$S1" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "1.5*$S1" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "0.5*$S2" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "0.75*$S2" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "2*$S2" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "4*$S2" | bc)
    ./main $D $R > logs/log_${D}_${R}
    R=$(echo "8*$S2" | bc)
    ./main $D $R > logs/log_${D}_${R}
done

# Limpiamos y acabamos
rm main
echo "Done!"
exit 0