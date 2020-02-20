#include "ParamSet.h"

void Object::add_attribute(string key, string value)
{
    attributes[key] = value;
}

void Object::print()
{
    map<string, string>::iterator it = attributes.begin();
    while (it != attributes.end())
    {
        string key = it->first;
        string value = it->second;

        cout << key << ", " << value << endl;
        it++;
    }
}

int main()
{
    Object o;
    o.type = "camera";
    o.add_attribute("type", "perspective");
    o.add_attribute("name", "cam_flat");
    o.print();
    return 0;
}
