#ifndef __INFACE_POWERSHELL_H__
#define __INFACE_POWERSHELL_H__

#include <Windows.h>
#include <string>

bool exec_powershell(const std::string &command, std::string &response)
{
    auto command_line = "powershell -Command \"" + command + "\"";
    auto fp = _popen(command_line.c_str(), "r");
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

bool unzip_file(const std::string &zip_file, const std::string &output_dir)
{
    std::string command = "Expand-Archive -Path " + zip_file + " -DestinationPath " + output_dir;
    std::string response;
    auto res = exec_powershell(command, response);
    if (!res)
        return false;
    // remove zip file
    DeleteFileA(zip_file.c_str());
    return true;
}

#endif // __INFACE_POWERSHELL_H__