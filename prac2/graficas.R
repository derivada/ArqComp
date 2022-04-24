library(ggplot2)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path)) # wd = carpeta contenedora del script (solo funciona en RSTUDIO)

# Preparar datos
datos = read.table("salida.txt", header = TRUE, sep = ",")

# Grafica de tamaño-ciclos para cada algoritmo
plot = ggplot(data = datos, mapping = aes(x = N, y = ck_medios)) +
  geom_line(aes(color = alg, group = alg), lwd = 1) +
  labs(title = "Comparación tamaño-ciclos",
       x = "N (Tamaño del problema)",
       y = "Ciclos de reloj por acceso") +
  theme_bw() +
  theme(legend.title = element_text(size = 25),
        legend.text = element_text(size=25),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))

ggsave("grafica.png", plot, width = 15, height = 10)

# Mostrar gráficas
plot