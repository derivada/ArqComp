ds = importdata ("results.csv", delimiterIn=",", headerLinesIn=1);

colors = ["r", "b", "g", "m", "k", "c"];

num_L=6;	%Numero de valores distintos de L
num_D=5;	%numero de valores distintos de D

%Gráfica de Ds
l = [];
array_plots = [];

for i = 1:num_D
    indexes = 1 + ((i-1)*num_L) : i*7;
    array_plots(i) = plot(ds.data(indexes, 3), ds.data(indexes, 5), "color", colors(i));
    l = [l ds.data(indexes(1), 1)];
    if (i == 1); hold on; endif;
endfor

title("Resultados de las ejecuciones");

legend(array_plots, cellstr(num2str(l', 'D=%-d')));
xlabel("L");
ylabel("ck medio");
print -djpg graphD-L.jpg;


%Para la gráfica de Ls
l = [];
array_plots = [];

for i = 1:num_L
    indexes = i : num_L : 35;
    array_plots(i) = plot(ds.data(indexes, 1), ds.data(indexes, 5), "color", colors(i));
    l = [l ds.data(indexes(1), 3)];
    if (i == 1); hold on; endif;
endfor

title("Resultados de las ejecuciones");

legend(array_plots, cellstr(num2str(l', 'L=%-d')));
xlabel("D");
ylabel("ck medio");
print -djpg graphL-D.jpg;
