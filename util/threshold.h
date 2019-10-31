#ifndef TRESHOLD_H
#define TRESHOLD_H

#include <algorithm>
#include <vector>
#include <cstring>
#include "base_filter.h"

namespace filter {
class threshold : public base
{
public:
    using base::base;
    void operator()( image_data &imgData, area const &ar )
    {
        // alias
        auto cpp = imgData.compPerPixel;

        if (cpp == 4 || cpp == 3) {
            int y0 = ar.top == 0 ? 0 : imgData.h / ar.top;
            int x0 = ar.left == 0 ? 0 : imgData.w / ar.left;
            stbi_uc *saved = new stbi_uc[imgData.h * imgData.w * cpp];
            if (saved == nullptr)
                throw "No memory";

            memcpy(saved, imgData.pixels, imgData.w * imgData.h * cpp);
            preprocess({saved, imgData.w, imgData.h, cpp});

            // pixel - center pixel
            auto applyMedian =
                    [&imgData, &ar, cpp, saved, x0, y0]( void ) -> void
            {
                int
                    xStart = x0,
                    yStart = y0,
                    xEnd = imgData.w / ar.right - 1,
                    yEnd = imgData.h / ar.bottom - 1;
                std::vector<int> indices((yEnd - yStart) * (xEnd - xStart));

                int i = 0;
                for (int y = yStart; y < yEnd; y++)
                    for (int x = xStart; x < xEnd; x++)
                        indices[i++] = (y * imgData.w + x) * cpp;

                std::sort(indices.begin(),
                          indices.end(),
                            [saved]( int idx1, int idx2 ) -> bool
                            {
                                return saved[idx1] < saved[idx2];
                            });

                for (int i = 0; i < indices.size() / 2; i++)
                {
                    imgData.pixels[indices[i] + 0] = 0;
                    imgData.pixels[indices[i] + 1] = 0;
                    imgData.pixels[indices[i] + 2] = 0;
                }
                for (int i = indices.size() / 2;
                     i < indices.size(); i++)
                {
                    imgData.pixels[indices[i] + 0] = saved[indices[i] + 0];
                    imgData.pixels[indices[i] + 1] = saved[indices[i] + 1];
                    imgData.pixels[indices[i] + 2] = saved[indices[i] + 2];
                }
            };

            applyMedian();

            delete []saved;
        }
    }
};

}
#endif // TRESHOLD_H
