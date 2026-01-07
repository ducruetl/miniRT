#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t stop = 0;

void handle_sigint(int sig) {
    stop = 1;
}

int main() {
    signal(SIGINT, handle_sigint);

    void *mlx = mlx_init();
    if (!mlx) {
        printf("Error: Failed to initialize MiniLibX.\n");
        return 1;
    }

    void *window = mlx_new_window(mlx, 720, 480, "Scene");
    if (!window) {
        printf("Error: Failed to create the window.\n");
        return 1;
    }

    sleep(2);    
    
    int code = mlx_destroy_window(mlx, window);
    if (code != 0) {
        printf("Error: Failed to destroy the window.\n");
        return code;
    }

    code = mlx_release(mlx);
    if (code != 0) {
        printf("Error: Failed to release MiniLibX.\n");
        return code;
    }

    return 0;
}