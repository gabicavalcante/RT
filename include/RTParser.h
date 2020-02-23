#pragma once

#include <iostream>
#include <memory>
#include "tinyxml2.h"
#include "ParamSet.h"

class RTParser
{
private:
    std::shared_ptr<Object> valuePtr;
    std::shared_ptr<tinyxml2::XMLDocument> doc;

public:
    static std::shared_ptr<RTParser> create()
    {
        return std::make_shared<RTParser>(RTParser());
    }

    int read_file(const char *pFilename);
};