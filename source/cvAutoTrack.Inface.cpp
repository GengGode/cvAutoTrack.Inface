#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.network.h"
#include "Inface.powershell.h"
#include "Inface.library.h"
#include "errdef.h"
#include "string.match.h"

int get_last_error()
{
    return 0;
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

// check cvAutoTrack.dll is valid
bool check_impl_valid()
{
    // check cvAutoTrack.dll is valid
    FILE *fp = fopen("cvAutoTrack.dll", "rb");
    if (fp == nullptr)
        return false;
    fclose(fp);
    // auto version = get_impl_version();
    auto handle = load_impl("cvAutoTrack.dll");
    if (handle == nullptr)
        return false;
    free_impl(handle);
    return true;
}

int auto_init_impl_v7(std::string download_url)
{
    auto download_res = download_file(download_url, "cvAutoTrack.zip");
    if (!download_res)
        return error("download cvAutoTrack.dll failed");
    auto unzip_res = unzip_file("cvAutoTrack.zip", ".");
    if (!unzip_res)
        return error("unzip cvAutoTrack.dll failed");
    auto check_res = check_impl_valid();
    if (!check_res)
        return error("check cvAutoTrack.dll failed");
}

int auto_init_impl()
{
    if (check_impl_valid())
        return 0;

    std::string download_url;
    auto download_url_res = get_response("https://download.api.weixitianli.com/cvAutoTrack/downloadUrl", download_url);
    if (!download_url_res)
        return error("get download url failed");
    std::string download_hash;
    auto download_hash_res = get_response("https://download.api.weixitianli.com/cvAutoTrack/Hash", download_hash);
    if (!download_hash_res)
        return error("get download hash failed");
    std::string download_version;
    auto download_version_res = get_response("https://download.api.weixitianli.com/cvAutoTrack/Version", download_version);
    if (!download_version_res)
        return error("get download version failed");

    if (match(download_version, "7\\.\\d+\\.\\d+"))
    {
        auto auto_init_impl_res = auto_init_impl_v7(download_url);
    }
    else
    {
        return error("cvAutoTrack.dll version not support");
    }
    return 0;
}
// set callback
void set_callback(void *callback)
{
}

// proxy for cvAutoTrack.dll

bool api(const char *json, inface_string_ptr result)
{
    return false;
}
