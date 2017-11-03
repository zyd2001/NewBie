gcc utility.c newbie.tab.c newbie.yy.c compile.c evaluate.c interpreter.c main.c -ldl -o nb
gcc --shared NB_std.c utility.c -o NBLibstd.so -fPIC
gcc --shared NB_math.c utility.c -o NBLibmath.so -lm -fPIC
gcc --shared NB_io.c utility.c -o NBLibio.so -fPIC