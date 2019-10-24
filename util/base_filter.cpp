#include "base_filter.h"

std::map<std::string, filter::base *> filter::base::filters;

filter::base::base( std::string const &name, std::function<void(image_data const &)> preprocess ) :
    preprocess(preprocess)
{
    if (filters.find(name) == filters.end())
        filters[name] = this;
}
