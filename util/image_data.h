#ifndef IMAGED_DATA_H
#define IMAGED_DATA_H

#include "stb_image.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;
};

#endif // IMAGED_DATA_H
