#include "cvAutoTrack.Inface.h"
#include "global.define.h"
#include "Inface.define.h"
#include "Inface.regerr.h"
#include "string.convert.h"

bool cout_is_utf8()
{
    auto command = "chcp";
    auto res = get_command_result(command);
    if (res.find("65001") != std::string::npos)
        return true;
    return false;
}
bool cout_is_gbk()
{
    auto command = "chcp";
    auto res = get_command_result(command);
    if (res.find("936") != std::string::npos)
        return true;
    return false;
}

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
    result->context = std::to_string(index) + ":" +
#ifdef _DEBUG
                      location.m_path + ":" + std::to_string(location.m_lineno) + ":" + std::to_string(location.m_colno) + " " +
#endif
                      location.m_errmsg;
    if (cout_is_gbk())
        result->context = utils::utf8_to_gbk(result->context);
    return 0;
}
