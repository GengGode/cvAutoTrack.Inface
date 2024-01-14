#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

static int lasst_error = 0;

int get_last_error()
{
    return lasst_error;
}

int get_error_define_count()
{
    return ErrorInvoker::m_locations.size();
}

int get_error_define(int index, inface_string_ptr result)
{
    if (index < 0 || index >= ErrorInvoker::m_locations.size())
        return error("error index out of range");
    auto &location = ErrorInvoker::m_locations[index];
    result->context = location.m_path + ":" + std::to_string(location.m_lineno) + ":" + std::to_string(location.m_colno) + " " + location.m_errmsg;
    return 0;
}
