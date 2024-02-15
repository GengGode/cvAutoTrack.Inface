#include <cvAutoTrack.Inface.h>
#include "Inface.define.h"
#include "Inface.regerr.h"
#include "resource.version.hpp"

int get_inface_version(inface_string_ptr result)
{
    auto version = resource::version;
    auto err = set_string_context(result, version.c_str(), version.size());
    if (err != 0)
        return error("设置版本号失败");
    return 0;
}
