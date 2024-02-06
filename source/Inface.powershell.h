#ifndef __INFACE_POWERSHELL_H__
#define __INFACE_POWERSHELL_H__

#include "global.define.h"

inline bool exec_powershell(const std::string &command, std::string &response)
{
    auto command_line = "powershell -Command \"" + command + "\"";

    auto fp = popen(command_line.c_str(), "r");
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

inline std::string get_file_hash(const std::string &file)
{
    std::string command = "Get-FileHash \"" + file + "\" -Algorithm MD5 | Select-Object -ExpandProperty Hash";
    std::string response;
    exec_powershell(command, response);
    return response.substr(0, response.size() - 1);
}

#endif // __INFACE_POWERSHELL_H__