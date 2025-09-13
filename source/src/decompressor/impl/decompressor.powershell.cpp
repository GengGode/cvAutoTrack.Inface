#include "../decompressor-interface.h"
#include <filesystem>
#include <fstream>
#include <future>

#ifndef NOMINMAX
    #define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN

#pragma comment(lib, "version")
#define pipe_t HANDLE
#define popen _popen
#define pclose _pclose

struct decompressor_powershell : public decompressor_interface
{
    bool is_valid = false;
    decompressor_powershell() { is_valid = get_command_result("echo hi") == "hi"; }

    opt_err unzip_file(const std::string& zip_file, const std::string& to_dir) override
    {
        if (!is_valid)
            return __FUNCTION__ "Powershell不可用";
        if (!powershell_unzip_file(zip_file, to_dir))
            return __FUNCTION__ "解压失败";
        return nullptr;
    }
    opt_err unzip_file(const std::string& zip_file, const std::string& to_dir, std::function<void(int /*current*/, int /*total*/)> progress) override
    {
        if (!is_valid)
            return __FUNCTION__ "Powershell不可用";
        if (!powershell_unzip_file(zip_file, to_dir))
            return __FUNCTION__ "解压失败";
        return nullptr;
    }
    opt_err unzip_file(const std::string& zip_file, std::string& out_file_content) override
    {
        if (!is_valid)
            return __FUNCTION__ "Powershell不可用";
        out_file_content.clear();
        return nullptr;
    }
    opt_err get_file_md5(const std::string& file, std::string& md5) override
    {
        if (!is_valid)
            return __FUNCTION__ "Powershell不可用";
        md5 = powershell_get_file_hash(file);
        if (md5.empty())
            return __FUNCTION__ "获取文件hash失败";
        return nullptr;
    }

    std::string get_command_result(const std::string& command)
    {
        std::string result;
        auto fp = popen(command.c_str(), "r");
        if (fp == nullptr)
            return result;
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp) != nullptr)
        {
            result += buffer;
        }
        pclose(fp);
        return result;
    }
    bool powershell_exec(const std::string& command, std::string& response)
    {
        auto command_line = "powershell -Command \"" + command + "\"";
        response = get_command_result(command_line);
        return true;
    }
    bool powershell_unzip_file(const std::string& zip_file, const std::string& output_dir)
    {
        std::string command = "Expand-Archive -Path " + zip_file + " -DestinationPath " + output_dir + " -Force";
        std::string response;
        auto res = powershell_exec(command, response);
        if (!res)
            return false;
        return true;
    }
    std::string powershell_get_file_hash(const std::string& file)
    {
        std::string command = "Get-FileHash \"" + file + "\" -Algorithm MD5 | Select-Object -ExpandProperty Hash";
        std::string response;
        powershell_exec(command, response);
        return response.substr(0, response.size() - 1);
    }
};

std::unique_ptr<decompressor_interface> create_decompressor()
{
    return std::make_unique<decompressor_powershell>();
}
