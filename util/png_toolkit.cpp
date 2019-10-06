#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include "stb_image_write.h"
#include "png_toolkit.h"

png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}

float png_toolkit::mseDeviation( const png_toolkit &tool,
                              Error &err, int &diffPix, filter::base::area const &ar ) const
{
    float res = 0;
    diffPix = 0;

    if (imgData.w != tool.imgData.w ||
        imgData.h != tool.imgData.h) {
        err = Error::WrongSize;
        return -1;
    }

    auto sub = []( stbi_uc *v1, stbi_uc *v2 ) -> std::array<stbi_uc, 3> {
        std::array<stbi_uc, 3> res;
        for (size_t i = 0; i < 3; i++)
            res[i] = v1[i] - v2[i];
        return res;
    };

    auto euclNorm2 = []( std::array<stbi_uc , 3> const &v ) -> int {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    };

    if (tool.imgData.compPerPixel < 3 ||
            imgData.compPerPixel < 3) {
        err = Error::WrongFormat;
        return -1;
    }

    auto cpp = imgData.compPerPixel;

    int y = ar.top == 0 ? 0 : imgData.w / ar.top;
    int x = ar.left == 0 ? 0 : imgData.h / ar.left;
    int norm;
    for (; y < imgData.h / ar.bottom; y++)
        for (; x < (imgData.w / ar.right) * cpp; x += cpp)
    {
        norm = euclNorm2(sub(     imgData.pixels + y * imgData.w * cpp + x,
                             tool.imgData.pixels + y * imgData.w * cpp + x));
        diffPix += norm != 0;
        res += norm / float(imgData.w * imgData.h);
    }

    err = Error::Ok;
    return res;
}

image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}

void png_toolkit::applyFilter( filter::base &f, filter::base::area const &ar )
{
    f(imgData, ar);
}

