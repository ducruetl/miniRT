#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"

void draw_rectangle(struct img_data *img, int rect_width, int rect_height, int offset_x, int offset_y, unsigned int color)
{
    if (!img || !img->img_addr || rect_width <= 0 || rect_height <= 0)
        return;

    int max_w = img->width;
    int max_h = img->height;
    int bpp_bytes = img->bits_per_pixel / 8;

    if (max_w <= 0 || max_h <= 0 || bpp_bytes <= 0)
        return;

    int w = rect_width < max_w ? rect_width : max_w;
    int h = rect_height < max_h ? rect_height : max_h;

    for (int y = offset_y; y < h + offset_y; ++y) {
        unsigned char *row = img->img_addr + (y * img->line_length);
        for (int x = offset_x; x < w + offset_x; ++x) {
            unsigned char *pixel = row + x * bpp_bytes;
            *(unsigned int *)pixel = color;
        }
    }
}

void draw_circle(struct img_data *img, int radius, int offset_x, int offset_y, unsigned int color)
{
    if (!img || !img->img_addr || radius <= 0)
        return;

    int max_w = img->width;
    int max_h = img->height;
    int bpp_bytes = img->bits_per_pixel / 8;

    if (max_w <= 0 || max_h <= 0 || bpp_bytes <= 0)
        return;

    int r2 = radius * radius;

    for (int y = 0; y < max_h; ++y) {
        unsigned char *row = img->img_addr + (y * img->line_length);
        int dy = y - offset_y;
        for (int x = 0; x < max_w; ++x) {
            int dx = x - offset_x;
            if (dx * dx + dy * dy <= r2) {
                unsigned char *pixel = row + x * bpp_bytes;
                *(unsigned int *)pixel = color;
            }
        }
    }
}

void draw_triangle(struct img_data *img, int x_a, int y_a, int x_b, int y_b, int x_c, int y_c, unsigned int color)
{
    if (!img || !img->img_addr || x_a < 0 || y_a < 0 || x_b < 0 || y_b < 0 || x_c < 0 || y_c < 0)
        return;

    int max_w = img->width;
    int max_h = img->height;
    int bpp_bytes = img->bits_per_pixel / 8;

    if (max_w <= 0 || max_h <= 0 || bpp_bytes <= 0)
        return;

    int vec_ab = (x_b - x_a) + (y_b - y_a);
    int vec_ac = (x_c - x_a) + (y_c - y_a);

    int parameter = (vec_ab * vec_ac) / (vec_ab * vec_ab); 
    int x_projection = x_a + (x_b - x_a) * parameter;
    int y_projection = y_a + (y_b - y_a) * parameter;

    int base = (x_c - x_projection) + (y_c - y_projection);
    float area = (abs(base) * abs(vec_ab)) / 2;

    for (int y = 0; y < max_h; ++y) {
        unsigned char *row = img->img_addr + (y * img->line_length);
        for (int x = 0; x < max_w; ++x) {
            // First triangle part
            int vec_ap = (x - x_a) + (y - y_a);

            parameter = (vec_ab * vec_ap) / (vec_ab * vec_ab); 
            x_projection = x_a + (x_b - x_a) * parameter;
            y_projection = y_a + (y_b - y_a) * parameter;

            base = (x - x_projection) + (y - y_projection);
            float area1 = (abs(base) * abs(vec_ab)) / 2;

            // Second triangle part
            int vec_cp = (x - x_c) + (y - y_c);
            int vec_ca = (x_a - x_c) + (y_a - y_c);

            parameter = (vec_ca * vec_cp) / (vec_ca * vec_ca);
            x_projection = x_c + (x_a - x_c) * parameter;
            y_projection = y_c + (y_a - y_c) * parameter;

            base = (x - x_projection) + (y - y_projection);
            float area2 = (abs(base) * abs(vec_ca)) / 2;

            // Third triangle part
            int vec_bp = (x - x_b) + (y - y_b);
            int vec_bc = (x_c - x_b) + (y_c - y_b);

            parameter = (vec_bc * vec_bp) / (vec_bc * vec_bc);
            x_projection = x_b + (x_c - x_b) * parameter;
            y_projection = y_b + (y_c - y_b) * parameter;

            base = (x - x_projection) + (y - y_projection);
            float area3 = (abs(base) * abs(vec_bc)) / 2;

            // Point verification
            if (area1 + area2 + area3 != area) continue;
            
            unsigned char *pixel = row + x * bpp_bytes;
            *(unsigned int *)pixel = color;
        }
    }
}