#ifndef __INFACE_NETWORK_H__
#define __INFACE_NETWORK_H__

#include "global.define.h"

inline bool dowload_vaild()
{
    return system("curl --version");
}

inline bool cout_is_utf8()
{
    auto command = "chcp";
    auto res = get_command_result(command);
    if (res.find("65001") != std::string::npos)
        return true;
    return false;
}
inline bool cout_is_gbk()
{
    auto command = "chcp";
    auto res = get_command_result(command);
    if (res.find("936") != std::string::npos)
        return true;
    return false;
}

inline bool server_ssl_vaild()
{
    auto command = "curl -I https://download.api.weixitianli.com";
    auto res = get_command_result(command);
    if (res.find("200 OK") != std::string::npos)
        return true;
    return false;
}

inline std::string to_unvaild_ssl_url(const std::string &url)
{
    auto pos = url.find("https://");
    if (pos == std::string::npos)
        return url;
    return "http://" + url.substr(pos + 8);
}

inline std::string add_skip_ssl_param(const std::string &url)
{
    return to_unvaild_ssl_url(url) + " -k";
}

inline void check_or_create_path(const std::string &path)
{
    auto dir = std::filesystem::path(path);
    if (!std::filesystem::exists(dir))
        std::filesystem::create_directories(dir);
}

inline bool download_file(const std::string &url, const std::string &path)
{
    check_or_create_path(path);
    auto vaild_url = server_ssl_vaild() ? url : add_skip_ssl_param(url); // to_unvaild_ssl_url(url);
    auto command = "curl -L -o " + path + " " + vaild_url;
    auto ret = system(command.c_str());
    return ret == 0;
}

inline bool get_response(const std::string &url, std::string &response)
{
    auto vaild_url = server_ssl_vaild() ? url : add_skip_ssl_param(url); // to_unvaild_ssl_url(url);
    auto command = "curl " + vaild_url;
    response = get_command_result(command);
    return true;
}

#endif // __INFACE_NETWORK_H__
