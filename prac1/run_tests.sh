
# Obtener info de la cache
info_cache() {
    CACHE_LOG_FILE="cache_info.txt"
    if ! test -f $CACHE_LOG_FILE
    then
        touch $CACHE_LOG_FILE
    else
        rm $CACHE_LOG_FILE
    fi    
    # Tamaño L1
    aux=$(lscpu | grep "L1d cache:")
    aux=${aux##*[[:space:]][[:space:]]}
    tamanoL1=${aux%%[[:space:]]*}
    unidadL1=${aux##*[[:space:]]}
    echo "TamañoL1 = $tamanoL1 UnidadL1 = $unidadL1" >> $CACHE_LOG_FILE

    if [ $unidadL1 = "MiB" ]
    then
        tamanoL1=$(( $tamanoL1 * 1024 * 1024 ))
    elif [ $unidadL1 = "KiB" ]
    then
        tamanoL1=$(( $tamanoL1 * 1024 ))
    fi
    echo "L1 size (bytes)=$tamanoL1 bytes" >> $CACHE_LOG_FILE

    # Tamaño L2
    aux=$(lscpu | grep "L2 cache:")
    aux=${aux##*[[:space:]][[:space:]]}
    tamanoL2=${aux%%[[:space:]]*}
    unidadL2=${aux##*[[:space:]]}
    echo "TamañoL2 = $tamanoL2 UnidadL2 = $unidadL2" >> $CACHE_LOG_FILE

    if [ $unidadL2 = "MiB" ]
    then
        tamanoL2=$(( $tamanoL2 * 1024 * 1024 ))
    elif [ $unidadL2 = "KiB" ]
    then
        tamanoL2=$(( $tamanoL2 * 1024 ))
    fi
    echo "L2 size (bytes)=$tamanoL2 bytes" >> $CACHE_LOG_FILE

    # Numero de cores
    aux=$(lscpu | grep "^CPU(s):")
    nCores=${aux##*[[:space:]][[:space:]]}
    echo "nCores = $nCores" >> $CACHE_LOG_FILE

    # Tamaño de la línea CLS
    CLS=$(getconf LEVEL1_DCACHE_LINESIZE)
    echo "CLS = $CLS" >> $CACHE_LOG_FILE

    # Cantidad de lineas S1 y S2
    S1=$(( $tamanoL1 / ( $CLS * $nCores ) ))
    echo "S1 = $S1" >> $CACHE_LOG_FILE
    S2=$(( $tamanoL2 / ( $CLS * $nCores ) ))
    echo "S2 = $S2" >> $CACHE_LOG_FILE
}

info_cache

# Tomar  medidas  de  ciclos  para  los  siguientes  valores  de  
# L:  0.5*S1,  1.5*S1,  0.5*S2,  0.75*S2,  2*S2, 4*S2,  8*S2,  
# siendo  S1  el  número  de  líneas  caché  que  caben en  la  caché L1  de  datos  y  S2  el  número  de  líneas  caché que caben en la caché L2.
valoresD=(2 5 8 16 69) # 5 Valores de D elegidos entre 1 y 100

# Compilar el programa con las flags necesarias
gcc -o main main.c -O0 -msse3 -Wall -lm -pedantic 2> compl_errors.txt

# Crear el directorio de logs para las salidas del programa o limpiarlo 
if ! test -d "./logs"
then
    mkdir "./logs"
else
    rm ./logs/log*
fi

# Poner a punto el fichero de salida de resultados



# Ejecuta el programa para todos las combinaciones de D y R y lo guarda el archivo logs/log_D_R
for i in {1..10}
do
    RESULTS_FILE="results${i}.csv"
    if test -e $RESULTS_FILE
    then
        rm $RESULTS_FILE
    fi
    echo "D,R,L,ck,ck_medio" > $RESULTS_FILE
    for D in "${valoresD[@]}";
    do
        echo "Haciendo tests para D = $D, i = $i"
        L=$(echo "0.5*$S1" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "1.5*$S1" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "0.5*$S2" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "0.75*$S2" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "2*$S2" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "4*$S2" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
        L=$(echo "8*$S2" | bc)
        ./main $D $L $CLS $S1 $S2 $RESULTS_FILE > "logs/log_${D}_${L}.txt"
    done
done

# Combinar resultados
gcc -o mediana mediana.c -Wall -pedantic 2> compl_errors.txt

./mediana

# Limpiamos ejecutables
rm main
rm mediana

# Graficas
octave plots.m

echo "Done!"
exit 0