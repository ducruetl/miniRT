#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include "shapes.h"

void draw_rectangle(struct img_data *img, int rect_width, int rect_height, int offset_x, int offset_y)
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
            *(unsigned int *)pixel = img->color;
        }
    }
}

void draw_circle(struct img_data *img, int radius, int offset_x, int offset_y)
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
                *(unsigned int *)pixel = img->color;
            }
        }
    }
}