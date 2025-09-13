#pragma once
#include "cvautotrack-interface.h"
#include <string>

static inline void copy_to_string_span(const std::string& str, string_span& out_span)
{
    if (str.empty())
    {
        out_span.data = nullptr;
        out_span.size = 0;
        return;
    }

    out_span.data = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), out_span.data);
    out_span.data[str.size()] = '\0';
    out_span.size = str.size();
}