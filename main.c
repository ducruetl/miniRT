#include "mlx.h"
#include <stdio.h>

int main() {
    printf("Hello\n");
    void *mlx = mlx_init();
    mlx_release(mlx);
    return 0;
}