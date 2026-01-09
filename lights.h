#ifndef LIGHTS_H
#define LIGHTS_H

#include "shapes.h"

struct light_data
{
    int x;
    int y;
    int z;
    float brightness; // Between 0 and 1
    int color;
};

void apply_light(struct img_data *img, struct light_data *light);

#endif