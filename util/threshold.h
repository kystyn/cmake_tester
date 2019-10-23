#ifndef TRESHOLD_H
#define TRESHOLD_H

#include <algorithm>
#include <vector>
#include "base_filter.h"

namespace filter {
class threshold : public filter::base
{
public:
    using base::base;
    void operator()( image_data &imgData, area const &ar )
    {
        // alias
        auto cpp = imgData.compPerPixel;
        const int matrixSize = 3;
        std::array<int, matrixSize * matrixSize> indices;

        // pixel - center pixel
        auto applyMedian =
                [&imgData, cpp, &indices, matrixSize]( int pixelX, int pixelY, int channel ) -> void
        {
            int
                xStart = std::max(0, pixelX - matrixSize / 2),
                yStart = std::max(0, pixelY - matrixSize / 2),
                xEnd = std::min(imgData.w - 1, pixelX + matrixSize / 2),
                yEnd = std::min(imgData.h - 1, pixelY + matrixSize / 2);

            int i = 0;
            for (int y = yStart; y <= yEnd; y++)
                for (int x = xStart; x <= xEnd; x++)
                    indices[i++] = (y * imgData.w + x) * cpp  + channel;

            std::sort(indices.begin(),
                      indices.begin() + (yEnd - yStart + 1) * (xEnd - xStart + 1),
                        [&imgData]( int idx1, int idx2 ) -> bool
                        {
                            return imgData.pixels[idx1] < imgData.pixels[idx2];
                        });

            for (int i = 0; i < (yEnd - yStart + 1) * (xEnd - xStart + 1) / 2; i++)
                imgData.pixels[indices[i]] = 0;
        };

        if (cpp == 4 || cpp == 3) {
            int y = ar.top == 0 ? 0 : imgData.h / ar.top;
            for (; y < imgData.h / ar.bottom; y++) {
                int x = ar.left == 0 ? 0 : imgData.w / ar.left;
                for (; x < imgData.w / ar.right; x++)
                    for (int c = 0; c < 3; c++)
                        applyMedian(x, y, c);
            }
        }
    }
};

}
#endif // TRESHOLD_H
