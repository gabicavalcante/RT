#include "RTParser.h"

int RTParser::read_file(const char *pFilename)
{
    doc->LoadFile(pFilename);

    for (const tinyxml2::XMLElement *child = doc->FirstChildElement("raytracer")->FirstChildElement();
         child;
         child = child->NextSiblingElement())
    {
        if (child->Attribute("type"))
            valuePtr->add_attribute("type", child->Attribute("type"));

        if (child->Attribute("name"))
            valuePtr->add_attribute("name", child->Attribute("name"));
    }
    valuePtr->print();

    return 0;
}