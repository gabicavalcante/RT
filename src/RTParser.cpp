#include "RTParser.h"
#include "ParamSet.h"

int RTParser::read_file()
{
    std::shared_ptr<ParamSet> valuePtr;
    for (const tinyxml2::XMLElement *child = doc->FirstChildElement("RT3")->FirstChildElement();
         child;
         child = child->NextSiblingElement())
    {
        valuePtr = std::shared_ptr<ParamSet>(new ParamSet());
        //valuePtr->tag = child->Value();

        for (const tinyxml2::XMLAttribute *attr = child->FirstAttribute();
             attr;
             attr = attr->Next())
        {
            valuePtr->add_attribute(attr->Name(), attr->Value());
        }

        valuePtr->print();
        std::cout << "\n";
    }

    return 0;
}

ParamSet RTParser::read_object(const char *tag)
{
    ParamSet ps;
    const tinyxml2::XMLElement *child = doc->FirstChildElement("RT3")->FirstChildElement(tag);

    for (const tinyxml2::XMLAttribute *attr = child->FirstAttribute();
         attr;
         attr = attr->Next())
    {
        ps.add_attribute(attr->Name(), attr->Value());
    }

    return ps;
}