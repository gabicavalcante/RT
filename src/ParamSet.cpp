#include "ParamSet.h"

void Object::add_attribute(string key, string value)
{
    attributes[key] = value;
}

void Object::print()
{
    cout << ">> " << label << endl;
    map<string, string>::iterator it = attributes.begin();
    while (it != attributes.end())
    {
        string key = it->first;
        string value = it->second;

        cout << key << ", " << value << endl;
        it++;
    }
}
