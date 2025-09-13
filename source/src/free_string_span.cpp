#include "cvautotrack-interface.h"

void free_string_span(string_span* span)
{
    if (span != nullptr)
    {
        if (span->data != nullptr)
            delete[] span->data;
        delete span;
        span = nullptr;
    }
}
