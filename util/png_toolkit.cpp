#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include "stb_image_write.h"
#include "png_toolkit.h"

std::map<std::string, png_toolkit::Filter> png_toolkit::filters =
{
  {"fillHalfRed", Filter::FILL_HALF_RED}
};

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
                              Error &err, int &diffPix ) const
{
    int res = 0;
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

    for (int i = 0;
         i < imgData.w * imgData.h * imgData.compPerPixel;
         i += imgData.compPerPixel)
    {
        diffPix += euclNorm2(sub(imgData.pixels + i, tool.imgData.pixels + i)) != 0;
        res += euclNorm2(sub(imgData.pixels + i, tool.imgData.pixels + i));
    }

    err = Error::Ok;
    return res / float(imgData.w * imgData.h);
}

image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}

void png_toolkit::applyFilter( Filter f )
{
    switch (f) {
    case Filter::FILL_HALF_RED:
        fillHalfRed();
        break;
    }
}

void png_toolkit::fillHalfRed()
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
