#ifndef BASE_FILTER_H
#define BASE_FILTER_H

#include <map>
#include <string>
#include <functional>
#include <algorithm>
#include "image_data.h"

namespace filter {
class base
{
public:
    /* ATTENTION
     * these vars are DIVISORS excepted 0
     * so if u see top = 5 it means that top is 1 / 5 of width
     * BUT
     * if u see 0 it means 0
     */
    struct area {
        int top, left, bottom, right;
    };

    base( std::string const &name, std::function<void(image_data const &)> preprocess = []( image_data const & ){} );

    virtual void operator()( image_data &imgData, area const &ar ) = 0;

    static std::map<std::string, filter::base *> const & getFilters( void )
    {
        return filters;
    }

    void clamp( int *c )
    {
        for (int i = 0; i < 3; i++)
            c[i] = std::max(0, std::min(255, c[i]));
    }

    void clamp( stbi_uc *c )
    {
        for (int i = 0; i < 3; i++)
            c[i] = std::max<stbi_uc>(0, std::min<stbi_uc>(255, c[i]));
    }

protected:
    std::function<void( image_data const & )> preprocess;
private:
    static std::map<std::string, filter::base *> filters;
};
}
#endif // BASE_FILTER_H
