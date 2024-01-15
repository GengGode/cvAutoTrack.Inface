#ifndef __INFACE_POWERSHELL_H__
#define __INFACE_POWERSHELL_H__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <string>

inline bool exec_powershell(const std::string &command, std::string &response)
{
    auto command_line = "powershell -Command \"" + command + "\"";
    
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    auto fp = _popen(command_line.c_str(), "r");
#else
    auto fp = popen(command_line.c_str(), "r");
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

inline bool unzip_file(const std::string &zip_file, const std::string &output_dir)
{
    std::string command = "Expand-Archive -Path " + zip_file + " -DestinationPath " + output_dir;
    std::string response;
    auto res = exec_powershell(command, response);
    if (!res)
        return false;
    // remove zip file
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    DeleteFileA(zip_file.c_str());
#else
    unlink(zip_file.c_str());
#endif
    return true;
}

#endif // __INFACE_POWERSHELL_H__