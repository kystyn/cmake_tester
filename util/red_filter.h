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
            for (; y < imgData.h / ar.bottom; y++) {
                int x = ar.left == 0 ? 0 : imgData.w / ar.left;
                for (; x < imgData.w / ar.right; x++)
                {
                    imgData.pixels[(y * imgData.w + x) * cpp + 0] = 255;
                    imgData.pixels[(y * imgData.w + x) * cpp + 1] = 0;
                    imgData.pixels[(y * imgData.w + x) * cpp + 2] = 0;
                    imgData.pixels[(y * imgData.w + x) * cpp + 3] = 255;
                }
            }
        }
    }
};
}

#endif // RED_FILTER_H
