#ifndef SHAPES_H
#define SHAPES_H

struct img_data
{
    int width;
    int height;
    void *img_ptr;
    unsigned char *img_addr;
    unsigned int bits_per_pixel;
    unsigned int line_length;
    unsigned int endian;
};

void draw_rectangle(struct img_data *img, int rect_width, int rect_height, int offset_x, int offset_y, unsigned int color);
void draw_circle(struct img_data *img, int radius, int offset_x, int offset_y, unsigned int color);
void draw_triangle(struct img_data *img, int x_a, int y_a, int x_b, int y_b, int x_c, int y_c, unsigned int color);

#endif