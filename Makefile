main: main.c
	gcc -o miniRT main.c shapes.c -Imlx/src -Lmlx -lmlx -lm -Wl,-rpath=./mlx