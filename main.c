#include "mlx.h"
#include "shapes.h"
#include <math.h>
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

    unsigned int color = (alpha << 24) | (red << 16) | (green << 8) | blue;

    struct img_data img;
    img.width = 720;
    img.height = 480;
    img.img_ptr = mlx_new_image(mlx_ptr, img.width, img.height);
    img.img_addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

    draw_circle(&img, 30, 30, 60, color);
    draw_circle(&img, 100, 400, 300, color);
    draw_rectangle(&img, 50, 20, 200, 150, color);
    draw_triangle(&img, 10, 10, 50, 10, 10, 50, color);

    mlx_put_image_to_window(mlx_ptr, window, img.img_ptr, 0, 0);

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