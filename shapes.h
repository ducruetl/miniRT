#ifndef SHAPES_H
#define SHAPES_H

struct img_data
{
    int width;
    int height;
    unsigned int color;
    void *img_ptr;
    unsigned char *img_addr;
    unsigned int bits_per_pixel;
    unsigned int line_length;
    unsigned int endian;
};

void draw_rectangle(struct img_data *img, int rect_width, int rect_height, int offset_x, int offset_y);
void draw_circle(struct img_data *img, int radius, int offset_x, int offset_y);

#endif