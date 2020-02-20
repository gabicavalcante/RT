#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class ValueBase
{
public:
    void print();
};

template <class T>
class Value : public ValueBase
{
public:
    T value;

public:
    Value(T value);
    T getvalue();
    void print();
};

class Object
{
public:
    string type;
    map<string, ValueBase *> attributes;

    void add_attribute(string key, ValueBase value);
    void print();
};