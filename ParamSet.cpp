// param set structure
// 18/02

#include "ParamSet.h"

template <class T>
Value<T>::Value(T val)
{
    value = val;
}

template <class T>
T Value<T>::getvalue()
{
    return value;
}

void ValueBase::print()
{
}

template <class T>
void Value<T>::print()
{
    cout << value << " valor";
}

void Object::add_attribute(string key, ValueBase value)
{
    attributes[key] = &value;
}

void Object::print()
{
    map<string, ValueBase *>::iterator it = attributes.begin();
    while (it != attributes.end())
    {
        string key = it->first;
        ValueBase *value = it->second;

        cout << key << endl;
        printf("value: %d\n", (void *)value);

        it++;
    }
}

void print_object(Object object)
{
    map<string, ValueBase *>::iterator it = object.attributes.begin();
    while (it != object.attributes.end())
    {
        string key = it->first;

        cout << key << endl;
        printf("value: %d\n", (*it->second));

        it++;
    }
}

int main()
{
    Value<int> size(2);
    //cout << size.getvalue() << endl;

    Object o;
    o.type = "camera";
    o.add_attribute("size", size);
    o.print();
    return 0;
}
