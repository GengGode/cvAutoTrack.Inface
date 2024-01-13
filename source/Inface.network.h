#ifndef __INFACE_NETWORK_H__
#define __INFACE_NETWORK_H__

#include <windows.h>
#include <string>

bool dowload_vaild()
{
    return system("curl --version");
}

bool download_file(const std::string &url, const std::string &path)
{
    auto command = "curl -L -o " + path + " " + url;
    auto ret = system(command.c_str());
    return ret == 0;
}

bool get_response(const std::string &url, std::string &response)
{
    auto command = "curl " + url;
    auto fp = _popen(command.c_str(), "r");
    if (fp == nullptr)
        return false;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        response += buffer;
    }
    _pclose(fp);
    return true;
}

#endif // __INFACE_NETWORK_H__
