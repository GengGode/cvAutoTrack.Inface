#include "cvAutoTrack.Inface.h"
#include "string.match.h"
#include "Inface.regerr.h"
#include "Inface.define.h"
#include "Inface.library.h"
#include "Inface.network.h"
#include "Inface.powershell.h"

int get_online_core_latest_version(inface_string_ptr result)
{
    auto url = get_value("项目链接") + "/LatestVersion";
    std::string latest_version;
    auto res = get_response(url, latest_version);
    if (!res)
        return error("获取最新版本失败");
    auto err = set_string_context(result, latest_version.c_str(), latest_version.size());
    if (err != 0)
        return error("设置最新版本失败");
    return 0;
}
int get_online_core_version_list(inface_string_ptr result)
{
    auto url = get_value("项目链接") + "/Versions";
    std::string version_list;
    auto res = get_response(url, version_list);
    if (!res)
        return error("获取版本列表失败");
    auto err = set_string_context(result, version_list.c_str(), version_list.size());
    if (err != 0)
        return error("设置版本列表失败");
    return 0;
}
int get_online_core_version_info(const char *version, inface_string_ptr result)
{
    auto url = get_value("项目链接") + "/" + version;
    std::string version_info;
    auto res = get_response(url, version_info);
    if (!res)
        return error("获取版本信息失败");
    auto err = set_string_context(result, version_info.c_str(), version_info.size());
    if (err != 0)
        return error("设置版本信息失败");
    return 0;
}
