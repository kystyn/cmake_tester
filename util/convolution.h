#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <array>
#include <cstring>
#include "base_filter.h"

namespace filter {

template<int N>
class convolution : public base {
public:
    convolution( std::string const &filterName, std::array<std::array<double, N>, N> const &ker ) :
        base(filterName), ker(ker) {}

    void operator()( image_data &imgData, area const &ar ) override
    {
        auto cpp = imgData.compPerPixel;
        if (cpp == 4 || cpp == 3) {
            const int matrixSize = N;
            int x = ar.left == 0 ? 0 : imgData.w / ar.left;
            int y = ar.top == 0 ? 0 : imgData.h / ar.top;

            stbi_uc *saved = new stbi_uc[imgData.h * imgData.w * cpp];
            if (saved == nullptr)
                throw "No memory";

            memcpy(saved, imgData.pixels, imgData.w * imgData.h * cpp);

            double norm = 0;

            for (auto y : ker)
                for (auto x : y)
                    norm += x;

            auto convolute =
                [&, imgData, cpp, matrixSize, saved, norm]( int pixelX, int pixelY, stbi_uc *resC ) -> void
            {
                int
                    xStart = std::max(0, pixelX - matrixSize / 2),
                    yStart = std::max(0, pixelY - matrixSize / 2),
                    xEnd = std::min(imgData.w - 1, pixelX + matrixSize / 2),
                    yEnd = std::min(imgData.h - 1, pixelY + matrixSize / 2);

                double newC[3] = {0};
                for (int y = -N / 2; y <= N / 2; y++)
                    for (int x = -N / 2; x <= N / 2; x++)
                        if (pixelY + y >= yStart && pixelY + y <= yEnd &&
                            pixelX + x >= xStart && pixelX + x <= xEnd)
                            for (int c = 0; c < 3; c++)
                                newC[c] +=
                                        saved[((pixelY + y) * imgData.w + pixelX + x) * cpp + c] *
                                        ker[y + N / 2][x + N / 2] / norm;


                resC[0] = stbi_uc(newC[0]);
                resC[1] = stbi_uc(newC[1]);
                resC[2] = stbi_uc(newC[2]);
            };

            for (; y < imgData.h / ar.bottom; y++)
            {
                x = ar.left == 0 ? 0 : imgData.w / ar.left;
                for (; x < imgData.w / ar.right; x++)
                    convolute(x, y, imgData.pixels + (y * imgData.w + x) * cpp);
            }
        }
    }

private:
    std::array<std::array<double, N>, N> ker;
};
}

#endif // CONVOLUTION_H
