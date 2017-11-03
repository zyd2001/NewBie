gcc utility.c newbie.tab.c newbie.yy.c compile.c evaluate.c interpreter.c main.c -o nb -liconv
gcc --shared NB_std.c utility.c -o NBLibstd.dll -fPIC -liconv
gcc --shared NB_math.c utility.c -o NBLibmath.dll -fPIC -liconv
gcc --shared NB_io.c utility.c -o NBLibio.dll -fPIC -liconv
