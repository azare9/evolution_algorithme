set terminal jpeg
set grid
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi 0 ps 0.2
set pointintervalbox 1
set output "./testGA.jpeg"
set xrange[0:1]
plot "./testGA.txt" pt 2 ps 2, sin(10*x)*sin(10*x)/(1+x) with linespoints ls 1 lc rgb "blue"
