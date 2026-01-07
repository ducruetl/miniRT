main: main.c
	gcc -o miniRT main.c -Imlx/src -Lmlx -lmlx -ldl -lGL -lm -lpthread -Wl,-rpath=./mlx