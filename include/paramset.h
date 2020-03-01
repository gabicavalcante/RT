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

    void add_attribute(std::string key, std::string value);
    std::string get_attribute(std::string key);
    void print();
};
