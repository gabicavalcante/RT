#include "api.h"

API *API::instance = 0;

API *API::get_instance()
{
    if (instance == 0)
    {
        instance = new API();
    }

    return instance;
}

API::API() {}