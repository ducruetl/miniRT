#ifndef CAMERA_H
#define CAMERA_H

struct camera_data
{
    int x;
    int y;
    int z;
    float x_orientation; // [-1,1]
    float y_orientation; // [-1,1]
    float z_orientation; // [-1,1]
    int fov; // [0,180]
};

#endif