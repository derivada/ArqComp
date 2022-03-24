# En este script de R usando las librerías ggplot2 y plotly obtenemos las gráficas mostradas
# en la memoria de la práctica
library(ggplot2)
library(plotly)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path)) # wd = carpeta contenedora del script (solo funciona en RSTUDIO)

datos = read.table("results.csv", header = TRUE, sep = ",")

# Agrupar datos D y L
datos$D = factor(datos$D)
datos$L = factor(datos$L)

# Grafica D agrupado por L
plotL = ggplot(data = datos, mapping = aes(x = D, y = ck_medio)) +
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
ggsave("grafica_agrup_L.png", plotL, width = 15, height = 10)
plotL

# Grafica L agrupado por D
plotD = ggplot(data = datos, mapping = aes(x = L, y = ck_medio)) +
  geom_line(aes(color = D, group = D), lwd = 2) +
  labs(title = "Comparación lineas consultadas-ciclos",
       x = "L (líneas de caché consultadas)",
       y = "Ciclos de reloj por acceso",
       fill = "D") +
  theme_bw() +
  theme(legend.title = element_text(size = 25),
        legend.text = element_text(size=25),
        legend.key.size = unit(1, 'cm'),
        axis.title.x = element_text(size = 20),
        axis.title.y = element_text(size = 20),
        axis.text.x = element_text(size = 30),
        axis.text.y = element_text(size = 30),
        title = element_text(size = 25))
ggsave("grafica_agrup_D.png", plotD, width = 15, height = 10)

# Refrescar datos
datos = read.table("results.csv", header = TRUE, sep = ",")

# Grafica 3D D-L-CK con plotly
plot3D <- plot_ly(datos, x = ~D, y = ~L, z = ~ck_medio, color = ~ck_medio)
plot3D <- plot3D %>% add_markers()
plot3D <- plot3D %>% layout(scene = list(xaxis = list(title = 'D'),
                                   yaxis = list(title = 'L'),
                                   zaxis = list(title = 'ck_medio'))
                            )

htmlwidgets::saveWidget(plot3D, "3dplot.html")


# Grafica L/R (No se usó al final)
#datos$LOC = datos$L / datos$R

#plotLOC = ggplot(data = datos, mapping = aes(x = LOC, y = ck_medio)) +
#  geom_point(aes(color = factor(L), group = factor(L))) +
#  stat_summary(fun.data=mean_cl_normal) + 
#  geom_smooth(method='lm', formula= y~x) +
#  labs(title = "Comparación de una medida de localidad con ck_medio, agrupado por el salto entre elementos D",
#       x = "Localidad = L/R",
#       y = "Ciclos de reloj por acceso",
#       fill = "D") +
#  theme_bw()
#ggsave("grafica_localidad.png", plotLOC, width = 15, height = 10)

# Mostrar gráficas
plotD
plotL
plot3D
#plotLOC