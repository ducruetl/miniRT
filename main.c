#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define KEYCODE_ESCAPE 65307

int handle_close(unsigned int keycode, void *mlx_ptr) {
    if (keycode == KEYCODE_ESCAPE) { 
        return mlx_loop_exit(mlx_ptr);
    }

    return 0;
}

int main() {
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr) {
        printf("Error: Failed to initialize MiniLibX.\n");
        return 1;
    }

    void *window = mlx_new_window(mlx_ptr, 720, 480, "Scene");
    if (!window) {
        printf("Error: Failed to create the window.\n");
        return 1;
    }

    unsigned int red = 255;
    unsigned int green = 0;
    unsigned int blue = 255;
    unsigned int alpha = 255;

    unsigned int color = (alpha << 24) | (blue << 16) | (green << 8) | red;

    void *image = mlx_new_image(mlx_ptr, 100, 120);
    mlx_put_image_to_window(mlx_ptr, window, image, 100, 150);
    unsigned int bits_per_pixel;
    unsigned int line_size;
    unsigned int endian;
    unsigned char *image_addr = mlx_get_data_addr(image, &bits_per_pixel, &line_size, &endian);
    printf("bpp=%d line_len=%d endian=%d\n", bits_per_pixel, line_size, endian);


    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 100; j++) {
            char *pixel = image_addr + (i * line_size + j * (bits_per_pixel / 8));
            *(unsigned int *)pixel = color;
        }
    }

    mlx_key_hook(window, &handle_close, mlx_ptr);
    printf("Starting loop\n");
    mlx_loop(mlx_ptr);
    
    int code = mlx_destroy_window(mlx_ptr, window);
    if (code != 0) {
        printf("Error: Failed to destroy the window.\n");
        return code;
    }

    code = mlx_release(mlx_ptr);
    if (code != 0) {
        printf("Error: Failed to release MiniLibX.\n");
        return code;
    }

    return 0;
}