#include "cvautotrack-interface.h"
#include <global-variables-pool.hpp>

#include <configer-interface.h>
#include <decompressor-interface.h>
#include <downloader-interface.h>

#include "string_span.h"

auto get_configer()
{
    auto cfg = global::onlyone::get<configer_interface>();
    if (cfg == nullptr)
        cfg = global::set<configer_interface>(std::move(create_configer()));
    return cfg;
}
auto get_decompressor()
{
    auto dcmp = global::onlyone::get<decompressor_interface>();
    if (dcmp == nullptr)
        dcmp = global::set<decompressor_interface>(std::move(create_decompressor()));
    return dcmp;
}
auto get_downloader()
{
    auto dler = global::onlyone::get<downloader_interface>();
    if (dler == nullptr)
        dler = global::set<downloader_interface>(std::move(create_downloader()));
    return dler;
}

bool check_online_usable()
{
    auto cfg = get_configer();
    if (cfg == nullptr)
        return false;

    auto dler = get_downloader();
    if (dler == nullptr)
        return false;

    auto online_check_url = cfg->get("online_check_url", "https://gitee.com/suixian/cvAutoTrack/releases");

    std::string content;
    auto ret = dler->download_url(online_check_url, content);
    if (!ret)
        return false;
    return true;
}

opt_err get_online_usable_version_list(string_span* out_versions)
{
    auto cfg = get_configer();
    if (cfg == nullptr)
        return __FUNCTION__ "configer not initialized";

    auto dler = get_downloader();
    if (dler == nullptr)
        return __FUNCTION__ "downloader not initialized";

    if (out_versions == nullptr)
        return __FUNCTION__ "out_versions is nullptr";

    auto online_version_list_url = cfg->get("online_version_list_url", "https://gitee.com/suixian/cvAutoTrack/releases");

    std::string content;
    auto ret = dler->download_url(online_version_list_url, content);
    if (!ret)
        return ret;

    copy_to_string_span(content, *out_versions);

    return nullptr;
}

opt_err checkout_local_version(const char* version);
opt_err checkout_online_version(const char* version);
opt_err checkout_version_priority_local(const char* version);
opt_err checkout_version_priority_online(const char* version);
