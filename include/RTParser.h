#pragma once

#include <iostream>
#include <memory>
#include "tinyxml2.h"
#include "ParamSet.h"

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

    int read_file();
    ParamSet read_object(const char *tag);
};