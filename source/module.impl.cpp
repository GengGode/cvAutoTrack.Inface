#include "cvAutoTrack.Inface.h"
#include "string.match.h"
#include "Inface.regerr.h"
#include "Inface.define.h"
#include "Inface.library.h"
#include "Inface.network.h"
#include "Inface.powershell.h"

int load_impl_and_deps()
{
    set_deps_path(get_value("加载目录"));
    set_deps_path(get_value("依赖目录"));
    set_deps_path(get_value("资源目录"));
    if (!auto_load_impl(get_value("加载目录", "库文件名"), true))
        return error("加载cvAutoTrack.dll失败");
    return 0;
}

// check cvAutoTrack.dll is valid
bool check_impl_valid()
{
    auto cvat_file = get_value("加载目录", "库文件名");

    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return false;
    fclose(fp);

    set_deps_path(get_value("加载目录"));
    set_deps_path(get_value("依赖目录"));
    set_deps_path(get_value("资源目录"));
    auto handle = load_impl(cvat_file);
    if (handle == nullptr)
        return false;
    free_impl(handle);
    return true;
}

bool check_is_need_update()
{
    bool is_force_local = get_value("强制使用本地版本") == "true";
    if (is_force_local)
        return false;
    auto cvat_file = get_value("加载目录", "库文件名");
    auto local_version = get_dll_file_version(cvat_file);
    if (local_version.empty())
        return true;
    std::string download_version;
    auto download_version_res = get_response(get_value("项目链接") + "/LatestVersion", download_version);
    if (!download_version_res)
        return false;
    return download_version > local_version;
}

bool check_file_hash(const std::string &file, const std::string &hash)
{
    auto hash_res = get_file_hash(file);
    if (hash_res != hash)
        return false;
    return true;
}

int download_core(version_info &info)
{
    auto url_file_name = info.url.substr(info.url.find_last_of('/') + 1);
    auto cvat_cache_file = get_value("下载目录") + url_file_name;
    auto download_res = download_file(info.url, cvat_cache_file);
    if (!download_res)
        return error("下载cvAutoTrack.zip失败");
    auto hash_res = check_file_hash(cvat_cache_file, info.hash);
    if (!hash_res)
        return error("校验cvAutoTrack.zip失败");
    auto cvat_dir = get_value("加载目录");
    auto unzip_res = unzip_file(cvat_cache_file, cvat_dir);
    if (!unzip_res)
        return error("解压cvAutoTrack.zip失败");

    auto cvat_file = get_value("加载目录", "库文件名");
    FILE *fp = fopen(cvat_file.c_str(), "rb");
    if (fp == nullptr)
        return error("没有找到cvAutoTrack.dll");
    fclose(fp);
    return 0;
}

int auto_init_impl_v7(version_info &info)
{
    return_if_err(download_core(info));

    return load_impl_and_deps();
}

int auto_init_impl_v8(version_info &info)
{
    return_if_err(download_core(info));

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
        auto depend_file = get_value("下载目录") + depend_url.substr(depend_url.find_last_of('/') + 1);
        debug_print("depend_file: %s\n", depend_file.c_str());
        debug_print("depend_hash: %s\n", depend_hash.c_str());
        debug_print("depend_url: %s\n", depend_url.c_str());

        if (!check_file_hash(depend_file, depend_hash))
            if (!download_file(depend_url, depend_file))
                return error("下载依赖文件失败");
        auto hash_res = check_file_hash(depend_file, depend_hash);
        if (!hash_res)
            return error("校验依赖文件失败");
        auto deps_dir = get_value("依赖目录");
        auto unzip_res = unzip_file(depend_file, deps_dir);
        if (!unzip_res)
            return error("解压依赖文件失败");
    }

    return load_impl_and_deps();
}

int get_latest_version(version_info &info)
{
    std::string download_url;
    auto download_url_res = get_response(get_value("项目链接") + "/downloadUrl", download_url);
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
    info.url = download_url;
    info.hash = download_hash;
    info.version = download_version;
    debug_print("url: %s\n", info.url.c_str());
    debug_print("hash: %s\n", info.hash.c_str());
    debug_print("version: %s\n", info.version.c_str());
    return 0;
}

int auto_init_impl()
{
    if (check_impl_valid() && !check_is_need_update())
    {
        return load_impl_and_deps();
    }

    version_info info;
    return_if_err(get_latest_version(info));

    switch (parse_major_version(info.version))
    {
    case 6:
        return error("不支持旧版本的cvAutoTrack.dll");
    case 7:
        return auto_init_impl_v7(info);
    case 8:
        return auto_init_impl_v8(info);
    default:
        return error("不支持的cvAutoTrack.dll版本");
    }
}