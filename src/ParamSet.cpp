#include "paramset.h"

void ParamSet::add_attribute(std::string key, std::string value)
{
    (*attributes)[key] = value;
}

std::string ParamSet::get_attribute(std::string key)
{
    return (*attributes)[key];
}

void ParamSet::print()
{
    std::cout << " --- " << std::endl;
    std::map<std::string, std::string>::iterator it = attributes->begin();
    while (it != attributes->end())
    {
        std::string key = it->first;
        std::string value = it->second;

        std::cout << key << " -> " << value << std::endl;
        it++;
    }
    std::cout << " --- " << std::endl;
}
