#pragma once

#include <iostream>
#include <memory>
#include "tinyxml2.h"
#include "paramset.h"
#include "api.h"

class RTParser
{
private:
    std::shared_ptr<tinyxml2::XMLDocument> doc;

    RTParser()
    {
        doc = std::shared_ptr<tinyxml2::XMLDocument>(new tinyxml2::XMLDocument());
    };

public:
    static std::shared_ptr<RTParser> create(std::string file_path)
    {
        RTParser p;
        p.doc->LoadFile(file_path.c_str());
        return std::make_shared<RTParser>(p);
    }

    void run()
    {
        auto api = API::get_instance();
        api->camera(read_object("camera"));
        api->film(read_object("film"));
        api->background(read_object("background"));
    }

    int read_file()
    {
        std::shared_ptr<ParamSet> valuePtr;
        for (const tinyxml2::XMLElement *child = doc->FirstChildElement("RT3")->FirstChildElement();
             child;
             child = child->NextSiblingElement())
        {
            valuePtr = std::shared_ptr<ParamSet>(new ParamSet());

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

    ParamSet read_object(const char *tag)
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
};
