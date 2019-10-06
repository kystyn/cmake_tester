#ifndef RED_FILTER_H
#define RED_FILTER_H

#include "base_filter.h"
#include "image_data.h"

namespace filter
{
class red : public base
{
    using base::base;

    void operator()( image_data &imgData, area const &ar ) override
    {
        // alias
        auto cpp = imgData.compPerPixel;
        if (cpp == 4 || cpp == 3) {
            int y = ar.top == 0 ? 0 : imgData.h / ar.top;
            int x = ar.left == 0 ? 0 : imgData.w / ar.left;
            for (; y < imgData.h / ar.bottom; y++)
                for (; x < (imgData.w / ar.right) * cpp; x += cpp)
                {
                    imgData.pixels[y * imgData.w * cpp + x + 0] = 255;
                    imgData.pixels[y * imgData.w * cpp + x + 1] = 0;
                    imgData.pixels[y * imgData.w * cpp + x + 2] = 0;
                }
        }
    }
};
}

#endif // RED_FILTER_H
