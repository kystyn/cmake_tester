#ifndef RED_FILTER_H
#define RED_FILTER_H

#include "base_filter.h"
#include "image_data.h"

namespace filter
{
class red : public base
{
    using base::base;

    void operator()( image_data &imgData ) override
    {
        // alias
        auto cpp = imgData.compPerPixel;
        if (imgData.compPerPixel == 4 || imgData.compPerPixel == 3)
            for (int y = imgData.h / 2; y < imgData.h; y++)
                for (int x = 0; x < imgData.w * cpp; x += cpp)
                {
                    imgData.pixels[y * imgData.w * cpp + x + 0] = 255;
                    imgData.pixels[y * imgData.w * cpp + x + 1] = 0;
                    imgData.pixels[y * imgData.w * cpp   + x + 2] = 0;
                }
    }
};
}

#endif // RED_FILTER_H
