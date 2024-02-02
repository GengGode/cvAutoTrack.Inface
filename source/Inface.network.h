#ifndef __INFACE_NETWORK_H__
#define __INFACE_NETWORK_H__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <windows.h>
#define pipe_t HANDLE
#define popen _popen
#define pclose _pclose
#else
#include <unistd.h>
#endif
#include <string>
#include <filesystem>

inline bool dowload_vaild()
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    return system("curl --version");
#else
    return system("curl --version") == 0;
#endif
}

inline bool server_ssl_vaild()
{
    auto command = "curl -I https://download.api.weixitianli.com";
    auto fp = popen(command, "r");
    if (fp == nullptr)
        return false;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        std::string line(buffer);
        if (line.find("HTTP/1.1 200 OK") != std::string::npos)
        {
            pclose(fp);
            return true;
        }
    }
    pclose(fp);
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
    auto fp = popen(command.c_str(), "r");
    if (fp == nullptr)
        return false;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        response += buffer;
    }
    pclose(fp);
    return true;
}

#endif // __INFACE_NETWORK_H__
