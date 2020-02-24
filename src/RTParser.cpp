#include "RTParser.h"
#include "ParamSet.h"

int RTParser::read_file()
{
    std::shared_ptr<Object> valuePtr;
    for (const tinyxml2::XMLElement *child = doc->FirstChildElement("RT3")->FirstChildElement();
         child;
         child = child->NextSiblingElement())
    {
        valuePtr = std::shared_ptr<Object>(new Object());
        valuePtr->label = child->Value();
        //std::cout << valuePtr->label << std::endl;

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
