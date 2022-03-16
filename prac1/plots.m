1  #!/usr/bin/env octave -q
ds = importdata ("results.csv", delimiterIn=",", headerLinesIn=1);

colors = ["r", "b", "g", "m", "k"];

l = [];

array_plots = [];

for i = 1:5
    indexes = ((i-1)*7)+1:i*7;
    array_plots(i) = plot(ds.data(indexes, 3), ds.data(indexes, 5), "color", colors(i));
    l = [l ds.data(indexes(1), 1)];
    if (i == 1); hold on; endif;
endfor

title("Resultados de las ejecuciones");

legend(array_plots, cellstr(num2str(l', 'D=%-d')));
xlabel("L");
ylabel("ck medio");
print -djpg graph.jpg