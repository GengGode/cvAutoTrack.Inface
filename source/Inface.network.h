#ifndef __INFACE_NETWORK_H__
#define __INFACE_NETWORK_H__

#include "global.define.h"
#include <fstream>
#include <future>

inline bool dowload_vaild()
{
    return system("curl --version");
}

inline bool server_ssl_vaild()
{
    return true;
    // auto command = "curl -I https://download.api.weixitianli.com";
    // auto res = get_command_result(command);
    // if (res.find("200 OK") != std::string::npos)
    //     return true;
    // return false;
}

inline std::string to_unvaild_ssl_url(const std::string& url)
{
    auto pos = url.find("https://");
    if (pos == std::string::npos)
        return url;
    return "http://" + url.substr(pos + 8);
}

inline std::string add_skip_ssl_param(const std::string& url)
{
    return to_unvaild_ssl_url(url) + " -k";
}

inline void check_or_create_path(const std::string& path)
{
    debug_print("check_or_create_path: %s\n", path.c_str());
    auto dir = std::filesystem::path(path).parent_path();
    if (!std::filesystem::exists(dir))
        std::filesystem::create_directories(dir);
}

inline bool download_file(const std::string& url, const std::string& path)
{
    debug_print("download_file: %s -> %s\n", url.c_str(), path.c_str());
    check_or_create_path(path);
    auto vaild_url = server_ssl_vaild() ? url : add_skip_ssl_param(url); // to_unvaild_ssl_url(url);
    auto command = "curl -L -o " + path + " " + vaild_url;
    auto ret = system(command.c_str());
    return ret == 0;
}

inline bool download_file(const std::string& url, const std::string& path, std::function<void(int, int)> progress)
{
    debug_print("download_file: %s -> %s\n", url.c_str(), path.c_str());
    check_or_create_path(path);
    auto vaild_url = server_ssl_vaild() ? url : add_skip_ssl_param(url); // to_unvaild_ssl_url(url);

    auto file_size = 0;
    auto command = "curl -I " + vaild_url;
    auto res = get_command_result(command);
    auto pos = res.find("Content-Length: ");
    if (pos != std::string::npos)
    {
        auto pos2 = res.find("\n", pos);
        file_size = std::stoi(res.substr(pos + 16, pos2 - pos - 16));
    }
    if (file_size <= 0)
        return false;
    command = "curl -L -o " + path + " " + vaild_url;
    if (progress == nullptr)
        return system(command.c_str()) == 0;
    std::future ret = std::async(std::launch::async, [command, progress]() { return system(command.c_str()); });
    while (ret.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready)
    {
        auto file = std::ifstream(path, std::ios::binary | std::ios::ate);
        auto size = file.tellg();
        file.close();
        progress(size, file_size);
    }
    return ret.get() == 0;
}

inline bool get_response(const std::string& url, std::string& response)
{
    debug_print("get_response: %s\n", url.c_str());
    auto vaild_url = server_ssl_vaild() ? url : add_skip_ssl_param(url); // to_unvaild_ssl_url(url);
    auto command = "curl -L " + vaild_url;
    response = get_command_result(command);
    return true;
}

#endif // __INFACE_NETWORK_H__
