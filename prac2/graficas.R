library(ggplot2)
library("ggrepel")                              
setwd(dirname(rstudioapi::getActiveDocumentContext()$path)) # wd = carpeta contenedora del script (solo funciona en RSTUDIO)

# Preparar datos
datos = read.table("salida.txt", header = TRUE, sep = ",")
# Mediana de todas las observaciones
datosCiclos <- aggregate( ck ~ N + alg, data = datos, median)
# Grafica de tamaño-ciclos totales para cada algoritmo
plotCiclos = ggplot(data = datosCiclos, mapping = aes(x = N, y = ck)) +
  geom_line(aes(color = alg, group = alg), lwd = 1) +
  labs(title = "Comparación tamaño - ciclos",
       x = "N (Tamaño del problema)",
       y = "Ciclos de reloj totales") +
  theme_bw() +
  theme(legend.title = element_text(size = 15),
        legend.text = element_text(size=15),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))

ggsave("graficaCiclos.png", plotCiclos, width = 15, height = 10)

datosSpeedup = datosCiclos
algBase = "Sec (O2)"
tiemposAlgBase = datosSpeedup[datosSpeedup$alg == algBase, ]
datosSpeedup$ck = apply(datosSpeedup, 1, function(x) {
  x[3] = tiemposAlgBase$ck[tiemposAlgBase$N == as.numeric(trimws(x[1], "both"))] / as.numeric(x[3])
})
colnames(datosSpeedup)[which(names(datosSpeedup) == "ck")] <- "speedup"                              
plotSpeedup = ggplot(data = datosSpeedup, mapping = aes(x = N, y = speedup)) +
  geom_line(aes(color = alg, group = alg), lwd = 1) +
  labs(title = "Speedup respecto al algoritmo secuencial",
       x = "N (Tamaño del problema)",
       y = "Veces más rápido") +
  theme_bw() +
  theme(legend.title = element_text(size = 15),
        legend.text = element_text(size=15),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))
  

ggsave("graficaSpeedup.png", plotSpeedup, width = 15, height = 10)
plotCiclos
plotSpeedup
tiemposOMP = datosSpeedup[substring(datosSpeedup$alg, 1, 3 ) == "OMP",]
tiemposOMP = tiemposOMP[tiemposOMP$N == 3000, ]
tiemposOMP$nThreads = as.numeric(substring(tiemposOMP$alg, 6,7))
plotThreads = ggplot(tiemposOMP,aes(x = nThreads, y = speedup), group = 1) +
  geom_line()+
  geom_point() +
  labs(title = "Speedup para N = 3000 para diferente número de hilos",
       x = "nThreads (Número de hilos usados)",
       y = "Veces más rápido respecto a sec.") +
  theme_bw() +
  theme(legend.title = element_text(size = 15),
        legend.text = element_text(size=15),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))
ggsave("graficaThreads.png", plotThreads, width = 15, height = 10)
plotThreads

