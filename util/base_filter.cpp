#include "base_filter.h"

std::map<std::string, filter::base *> filter::base::filters;

filter::base::base( std::string const &name )
{
    if (filters.find(name) == filters.end())
        filters[name] = this;
}
