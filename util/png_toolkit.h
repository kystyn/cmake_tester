#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include <map>
//#include <memory>
#include "stb_image.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;
};

class png_toolkit
{
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };

    enum class Filter {
        FILL_HALF_RED
    };

    png_toolkit();
    ~png_toolkit();
    bool load( std::string const &pictureName );
    bool save( std::string const &pictureName );
    float mseDeviation( png_toolkit const &tool, Error &err, int &diffPix ) const;
    image_data getPixelData( void ) const;
    void applyFilter( Filter f );
    void fillHalfRed( void );

    static std::map<std::string, Filter> filters;

private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H
