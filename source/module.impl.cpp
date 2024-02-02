#include "cvAutoTrack.Inface.h"
#include "string.match.h"
#include "Inface.regerr.h"
#include "Inface.define.h"
#include "Inface.library.h"
#include "Inface.network.h"
#include "Inface.powershell.h"

// check cvAutoTrack.dll is valid
bool check_impl_valid()
{
    auto cvat_file = inface_value_map["cvAutoTrack dll path"] + "\\" + inface_value_map["cvAutoTrack dll name"];
    // check cvAutoTrack.dll is valid
    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return false;
    fclose(fp);
    auto handle = load_impl(cvat_file);
    if (handle == nullptr)
        return false;
    free_impl(handle);
    return true;
}

int download_cvat(std::string download_url)
{
    auto cvat_dir = inface_value_map["cvAutoTrack dll path"];
    auto cvat_file = inface_value_map["cvAutoTrack dll path"] + "\\" + inface_value_map["cvAutoTrack dll name"];
    auto cvat_cache_file = inface_value_map["cvAutoTrack dll path"] + "\\" + inface_value_map["cvAutoTrack download cache name"];
    auto download_res = download_file(download_url, cvat_cache_file);
    if (!download_res)
        return error("download cvAutoTrack.zip failed");
    auto unzip_res = unzip_file(cvat_cache_file, cvat_dir);
    if (!unzip_res)
        return error("unzip cvAutoTrack.zip failed");
    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return error("cvAutoTrack.dll not found");
    fclose(fp);
    return 0;
}

int auto_init_impl_v7(std::string download_url)
{
    if (download_cvat(download_url) != 0)
        return error("download cvAutoTrack.dll failed");

    auto check_res = check_impl_valid();
    if (!check_res)
        return error("check cvAutoTrack.dll failed");

    auto cvat_file = inface_value_map["cvAutoTrack dll path"] + "\\" + inface_value_map["cvAutoTrack dll name"];
    auto load_res = auto_load_impl(cvat_file, true);
    if (!load_res)
        return error("load cvAutoTrack.dll failed");
    return 0;
}

int auto_init_impl_v8(std::string download_url)
{
    if (download_cvat(download_url) != 0)
        return error("download cvAutoTrack.dll failed");

    std::string download_depends;
    auto download_depends_res = get_response("https://download.api.weixitianli.com/cvAutoTrack/DependFilesDownloadUrlAndHash", download_depends);
    if (!download_depends_res)
        return error("get download depends failed");

    auto download_res = download_file(download_url, "cvAutoTrack.zip");
    if (!download_res)
        return error("download cvAutoTrack.dll failed");
    auto unzip_res = unzip_file("cvAutoTrack.zip", ".");
    if (!unzip_res)
        return error("unzip cvAutoTrack.dll failed");
    auto check_res = check_impl_valid();
    if (!check_res)
        return error("check cvAutoTrack.dll failed");

    // auto depends = split(download_depends, "\n");
    auto load_res = auto_load_impl("cvAutoTrack.dll", true);
    if (!load_res)
        return error("load cvAutoTrack.dll failed");
    return 0;
}

int auto_init_impl()
{
    if (check_impl_valid())
    {
        auto load_res = auto_load_impl("cvAutoTrack.dll");
        if (!load_res)
            return error("load cvAutoTrack.dll failed");
        return 0;
    }

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

    switch (parse_major_version(download_version))
    {
    case 6:
        return error("cvAutoTrack.dll version so old");
    case 7:
        return auto_init_impl_v7(download_url);
    case 8:
        return auto_init_impl_v8(download_url);
    default:
        return error("cvAutoTrack.dll version not support");
    }
}