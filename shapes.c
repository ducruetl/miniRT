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

    for (int y = offset_y; y < h + offset_y; ++y)
    {
        unsigned char *row = img->img_addr + (y * img->line_length);
        for (int x = offset_x; x < w + offset_x; ++x)
        {
            unsigned char *pixel = row + x * bpp_bytes;
            *(unsigned int *)pixel = color;
        }
    }
}

float calculate_area(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return 0.5f * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
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

    // Calcul de l'aire du triangle complet
    float area = calculate_area(x_a, y_a, x_b, y_b, x_c, y_c);

    for (int y = 0; y < max_h; ++y)
    {
        unsigned char *row = img->img_addr + (y * img->line_length);
        for (int x = 0; x < max_w; ++x)
        {
            // Calcul des aires des triangles formés par le point (x, y) avec chaque côté du triangle
            float area1 = calculate_area(x, y, x_b, y_b, x_c, y_c);
            float area2 = calculate_area(x_a, y_a, x, y, x_c, y_c);
            float area3 = calculate_area(x_a, y_a, x_b, y_b, x, y);

            // Si la somme des aires est égale à l'aire du triangle, le point (x, y) est à l'intérieur
            if (fabs(area - (area1 + area2 + area3)) < 1e-4)
            {
                unsigned char *pixel = row + x * bpp_bytes;
                *(unsigned int *)pixel = color;
            }
        }
    }
}

void draw_sphere(struct img_data *img, struct camera_data *cam, int x, int y, int z, int diameter, unsigned int color)
{
    int radius = diameter / 2;
    if (!img || !img->img_addr || radius <= 0)
        return;

    int max_w = img->width;
    int max_h = img->height;
    int bpp_bytes = img->bits_per_pixel / 8;

    if (max_w <= 0 || max_h <= 0 || bpp_bytes <= 0)
        return;

    
    int depth = z - cam->z;

    if (depth <= 0)
        return;

    int focal_length = max_w / (2 * tan(cam->fov / 2));
    radius = radius * focal_length / depth;
    int r2 = radius * radius;

    for (int screen_y = 0; screen_y < max_h; screen_y++)
    {
        unsigned char *row = img->img_addr + (screen_y * img->line_length);
        int dy = screen_y - y + cam->y;
        for (int screen_x = 0; screen_x < max_w; screen_x++)
        {
            int dx = screen_x - x + cam->x;
            if (dx * dx + dy * dy <= r2)
            {
                unsigned char *pixel = row + screen_x * bpp_bytes;
                *(unsigned int *)pixel = color;
            }
        }
    }
}