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
    auto cvat_file = get_value("加载目录", "库文件名");
    // check cvAutoTrack.dll is valid
    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return false;
    fclose(fp);
    set_deps_path(get_value("加载目录"));
    auto handle = load_impl(cvat_file);
    if (handle == nullptr)
        return false;
    free_impl(handle);
    return true;
}

bool check_file_hash(const std::string &file, const std::string &hash)
{
    auto hash_res = get_file_hash(file);
    if (hash_res != hash)
        return false;
    return true;
}

int download_cvat(std::string download_url)
{
    auto cvat_dir = get_value("加载目录");
    auto cvat_file = get_value("加载目录", "库文件名");
    auto url_file_name = download_url.substr(download_url.find_last_of('/') + 1);
    auto cvat_cache_file = get_value("加载目录") + url_file_name;
    auto download_res = download_file(download_url, cvat_cache_file);
    if (!download_res)
        return error("下载cvAutoTrack.zip失败");
    // auto unzip_res = unzip_file(cvat_cache_file, cvat_dir);
    // if (!unzip_res)
    //     return error("解压cvAutoTrack.zip失败");
    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return error("没有找到cvAutoTrack.dll");
    fclose(fp);
    return 0;
}

int auto_init_impl_v7(std::string download_url)
{
    if (download_cvat(download_url) != 0)
        return error("下载cvAutoTrack.dll失败");

    auto check_res = check_impl_valid();
    if (!check_res)
        return error("校验cvAutoTrack.dll失败");

    auto cvat_file = get_value("加载目录", "库文件名");
    auto load_res = auto_load_impl(cvat_file, true);
    if (!load_res)
        return error("加载cvAutoTrack.dll失败");
    return 0;
}

int auto_init_impl_v8(std::string download_url)
{
    if (download_cvat(download_url) != 0)
        return error("下载cvAutoTrack.dll失败");

    std::string download_depends;
    auto download_depends_res = get_response(get_value("依赖链接"), download_depends);
    if (!download_depends_res)
        return error("获取依赖文件列表失败");
    auto depends = split(download_depends, "\n");
    for (auto depend : depends)
    {
        auto depend_info = split(depend, "\\|");
        if (depend_info.size() != 2)
            continue;
        auto depend_hash = depend_info[0];
        auto depend_url = depend_info[1];
        auto depend_file = get_value("加载目录") + depend_url.substr(depend_url.find_last_of('/') + 1);
        auto download_res = download_file(depend_url, depend_file);
        if (!download_res)
            return error("下载依赖文件失败");
        auto hash_res = check_file_hash(depend_file, depend_hash);
        if (!hash_res)
            return error("校验依赖文件失败");
    }

    auto check_res = check_impl_valid();
    if (!check_res)
        return error("校验cvAutoTrack.dll失败");

    // auto depends = split(download_depends, "\n");
    auto cvat_file = get_value("加载目录", "库文件名");
    auto load_res = auto_load_impl(cvat_file, true);
    if (!load_res)
        return error("加载cvAutoTrack.dll失败");
    return 0;
}

int auto_init_impl()
{
    if (check_impl_valid())
    {
        set_deps_path(get_value("加载目录"));
        set_deps_path(get_value("依赖目录"));
        set_deps_path(get_value("资源目录"));
        if (!auto_load_impl(get_value("加载目录", "库文件名"), true))
            return error("加载cvAutoTrack.dll失败");
        return 0;
    }
    std::string download_url;
    auto download_url_res = get_response(get_value("项目链接") + "/downloadUrlAndHash", download_url);
    if (!download_url_res)
        return error("获取下载链接失败");
    std::string download_hash;
    auto download_hash_res = get_response(get_value("项目链接") + "/Hash", download_hash);
    if (!download_hash_res)
        return error("获取下载文件hash失败");
    std::string download_version;
    auto download_version_res = get_response(get_value("项目链接") + "/LatestVersion", download_version);
    if (!download_version_res)
        return error("获取cvAutoTrack.dll版本失败");

    switch (parse_major_version(download_version))
    {
    case 6:
        return error("不支持旧版本的cvAutoTrack.dll");
    case 7:
        return auto_init_impl_v7(download_url);
    case 8:
        return auto_init_impl_v8(download_url);
    default:
        return error("不支持的cvAutoTrack.dll版本");
    }
}