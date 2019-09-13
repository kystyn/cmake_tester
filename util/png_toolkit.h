#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include "base_filter.h"
#include "image_data.h"

class png_toolkit
{
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };

    png_toolkit();
    ~png_toolkit();
    bool load( std::string const &pictureName );
    bool save( std::string const &pictureName );
    float mseDeviation( png_toolkit const &tool, Error &err, int &diffPix ) const;
    image_data getPixelData( void ) const;
    void applyFilter( filter::base &f );

private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H
