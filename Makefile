main: main.c
	gcc -o miniRT main.c -Imlx/src -Lmlx -lmlx -Wl,-rpath=./mlx