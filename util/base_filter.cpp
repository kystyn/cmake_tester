#include "base_filter.h"

filter::base::base( std::string const &name )
{
    if (filters.find(name) == filters.end())
        filters[name] = this;
}
