#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class ParamSet
{
public:
    std::unique_ptr<std::map<string, string>> attributes;

    ParamSet()
    {
        std::map<string, string> map_({});
        attributes = std::make_unique<std::map<string, string>>(map_);
    }

    void add_attribute(string key, string value);
    void print();
};