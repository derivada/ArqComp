# En este script de R usando las librerías ggplot2 y plotly obtenemos las gráficas mostradas
# en la memoria de la práctica
library(ggplot2)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path)) # wd = carpeta contenedora del script (solo funciona en RSTUDIO)

datosSec = read.table("salidaSec.txt", header = TRUE, sep = ",")
datosSecOpt = read.table("salidaSecOpt.txt", header = TRUE, sep = ",")

# Agrupar datos D y L
# Grafica D agrupado por L
plot = ggplot(data = datos, mapping = aes(x = D, y = ck_medio)) +
  geom_line(aes(color = L, group = L), lwd = 2) +
  labs(title = "Comparación salto-ciclos",
       x = "D (Salto en memoria entre posiciones del array)",
       y = "Ciclos de reloj por acceso",
       fill = "L") +
  theme_bw() +
  theme(legend.title = element_text(size = 25),
        legend.text = element_text(size=25),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))
ggsave("grafica_comp.png", plotL, width = 15, height = 10)

# Mostrar gráficas
plot