#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

class ParamSet
{
public:
    std::unique_ptr<std::map<std::string, std::string>> attributes;

    ParamSet()
    {
        std::map<std::string, std::string> map_({});
        attributes = std::make_unique<std::map<std::string, std::string>>(map_);
    }

    void add_attribute(std::string key, std::string value)
    {
        (*attributes)[key] = value;
    }

    std::string get_attribute(std::string key)
    {
        return (*attributes)[key];
    }

    void print()
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
};