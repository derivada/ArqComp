library(ggplot2)
library(plotly)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path)) # wd = carpeta contenedora del script (solo funciona en RSTUDIO)

datos = read.table("results.csv", header = TRUE, sep = ",")

# Agrupar datos D y L
datos$D = factor(datos$D)
datos$L = factor(datos$L)

# Grafica D agrupado por L
plotD = ggplot(data = datos, mapping = aes(x = D, y = ck_medio)) +
  geom_line(aes(color = L, group = L)) +
  labs(title = "Comparación del valor de D con ck_medio, agrupado por el número de líneas L consultadas",
       x = "D (Salto en memoria entre posiciones del array)",
       y = "Ciclos de reloj por acceso",
       fill = "L") +
  theme_bw()
ggsave("grafica_agrup_L.png", plotL, width = 15, height = 10)

# Grafica L agrupado por D
plotL = ggplot(data = datos, mapping = aes(x = L, y = ck_medio)) +
  geom_line(aes(color = D, group = D)) +
  labs(title = "Comparación del valor de L con ck_medio, agrupado por el salto entre elementos D",
       x = "L (líneas de caché consultadas)",
       y = "Ciclos de reloj por acceso",
       fill = "D") +
  theme_bw()
ggsave("grafica_agrup_D.png", plotL, width = 15, height = 10)

# Refrescar datos
datos = read.table("results.csv", header = TRUE, sep = ",")

# Grafica 3D con plotly
plot3D <- plot_ly(datos, x = ~D, y = ~L, z = ~ck_medio, color = ~ck_medio)
plot3D <- plot3D %>% add_markers()
plot3D <- plot3D %>% layout(scene = list(xaxis = list(title = 'D'),
                                   yaxis = list(title = 'L'),
                                   zaxis = list(title = 'ck_medio'))
                            )

htmlwidgets::saveWidget(plot3D, "3dplot.html")

plotD
plotL
plot3D



