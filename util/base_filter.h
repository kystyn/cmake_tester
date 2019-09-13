#ifndef BASE_FILTER_H
#define BASE_FILTER_H

#include <map>
#include <string>
#include "image_data.h"

namespace filter {
class base
{
public:
    base( std::string const &name );

    virtual void operator()( image_data &imgData ) = 0;
    static std::map<std::string, filter::base *> filters;
};
}
#endif // BASE_FILTER_H
