#ifndef __INFACE_NETWORK_H__
#define __INFACE_NETWORK_H__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string>

inline bool dowload_vaild()
{
    
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    return system("curl --version");
#else
    return system("curl --version") == 0;
#endif
}

inline bool download_file(const std::string &url, const std::string &path)
{
    auto command = "curl -L -o " + path + " " + url;
    auto ret = system(command.c_str());
    return ret == 0;
}

inline bool get_response(const std::string &url, std::string &response)
{
    auto command = "curl " + url;
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    auto fp = _popen(command.c_str(), "r");
#else
    auto fp = popen(command.c_str(), "r");
#endif
    if (fp == nullptr)
        return false;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        response += buffer;
    }
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    _pclose(fp);
#else
    pclose(fp);
#endif
    return true;
}

#endif // __INFACE_NETWORK_H__
