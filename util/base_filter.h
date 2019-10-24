#ifndef BASE_FILTER_H
#define BASE_FILTER_H

#include <map>
#include <string>
#include <functional>
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

protected:
    std::function<void( image_data const & )> preprocess;
private:
    static std::map<std::string, filter::base *> filters;
};
}
#endif // BASE_FILTER_H
