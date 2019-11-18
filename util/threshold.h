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
        const int matrixSize = 5;
        std::array<int, matrixSize * matrixSize> indices;

        if (cpp == 4 || cpp == 3) {
            int y = ar.top == 0 ? 0 : imgData.h / ar.top, y0 = y;
            int x = ar.left == 0 ? 0 : imgData.w / ar.left, x0 = x;
            stbi_uc *saved = new stbi_uc[imgData.h * imgData.w * cpp];
            if (saved == nullptr)
                throw "No memory";

            memcpy(saved, imgData.pixels, imgData.w * imgData.h * cpp);
            preprocess({saved, imgData.w, imgData.h, imgData.compPerPixel});

            // pixel - center pixel
            auto applyMedian =
                    [&imgData, &ar, cpp, &indices, saved, x0, y0]( int pixelX, int pixelY ) -> void
            {
                int
                    xStart = std::max(x0, pixelX - matrixSize / 2),
                    yStart = std::max(y0, pixelY - matrixSize / 2),
                    xEnd = std::min(imgData.w / ar.right - 1, pixelX + matrixSize / 2),
                    yEnd = std::min(imgData.h / ar.bottom - 1, pixelY + matrixSize / 2);

                int i = 0;
                for (int y = yStart; y <= yEnd; y++)
                    for (int x = xStart; x <= xEnd; x++)
                        indices[i++] = (y * imgData.w + x) * cpp;

                std::stable_sort(indices.begin(),
                          indices.begin() + (yEnd - yStart + 1) * (xEnd - xStart + 1),
                            [saved]( int idx1, int idx2 ) -> bool
                            {
                                return saved[idx1] < saved[idx2];
                            });

                stbi_uc me = imgData.pixels[indices[(yEnd - yStart + 1) * (xEnd - xStart + 1) / 2]];

                for (int i = 0; i < 3; i++)
                    imgData.pixels[(pixelY * imgData.w + pixelX) * cpp + i] =
                    (saved[(pixelY * imgData.w + pixelX) * cpp + i] >= me) *
                            saved[(pixelY * imgData.w + pixelX) * cpp + i];
            };

            for (; y < imgData.h / ar.bottom; y++)
                for (x = ar.left == 0 ? 0 : imgData.w / ar.left; x < imgData.w / ar.right; x++)
                    applyMedian(x, y);

            delete []saved;
        }
    }
};

}
#endif // TRESHOLD_H
