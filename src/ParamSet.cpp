#include "paramset.h"

void ParamSet::add_attribute(string key, string value)
{
    (*attributes)[key] = value;
}

void ParamSet::print()
{
    cout << " --- " << endl;
    std::map<string, string>::iterator it = attributes->begin();
    while (it != attributes->end())
    {
        string key = it->first;
        string value = it->second;

        cout << key << " -> " << value << endl;
        it++;
    }
    cout << " --- " << endl;
}
