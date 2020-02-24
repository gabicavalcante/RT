#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class Object
{
public:
    string label;
    map<string, string> attributes;

    void add_attribute(string key, string value);
    void print();
};