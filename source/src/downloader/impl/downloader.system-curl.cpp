#include "../downloader-interface.h"
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

struct downloader_system_curl : public downloader_interface
{
    bool is_valid = false;
    downloader_system_curl() { is_valid = curl_has_valid(); }

    opt_err download_url(const std::string& url, std::string& content) override
    {
        if (!is_valid)
            return "curl不可用";
        if (!get_response(url, content))
            return "获取内容失败";
        return nullptr;
    }
    opt_err download_file(const std::string& url, const std::string& to_file) override
    {
        if (!is_valid)
            return "curl不可用";
        if (!curl_download_file(url, to_file))
            return "下载失败";
        return nullptr;
    }
    opt_err download_file(const std::string& url, const std::string& to_file, std::function<void(int /*current*/, int /*total*/)> progress) override
    {
        if (!is_valid)
            return "curl不可用";
        if (!curl_download_file(url, to_file, progress))
            return "下载失败";
        return nullptr;
    }

    bool curl_has_valid() { return system("curl --version") == 0; }
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
    bool get_response(const std::string& url, std::string& response)
    {
        auto command = "curl -L " + url;
        response = get_command_result(command);
        return true;
    }
    void check_or_create_path(const std::string& path)
    {
        auto dir = std::filesystem::path(path).parent_path();
        if (!std::filesystem::exists(dir))
            std::filesystem::create_directories(dir);
    }
    bool curl_download_file(const std::string& url, const std::string& path)
    {
        check_or_create_path(path);
        auto command = "curl -L -o " + path + " " + url;
        auto ret = system(command.c_str());
        return ret == 0;
    }
    bool curl_download_file(const std::string& url, const std::string& path, std::function<void(int, int)> progress)
    {
        check_or_create_path(path);

        auto file_size = 0;
        auto command = "curl -L -I " + url;
        auto res = get_command_result(command);
        auto pos = res.find("Content-Length: ");
        if (pos != std::string::npos)
        {
            auto pos2 = res.find("\n", pos);
            file_size = std::stoi(res.substr(pos + 16, pos2 - pos - 16));
        }
        if (file_size <= 0)
            return false;
        command = "curl -L -o " + path + " " + url;
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
};

std::unique_ptr<downloader_interface> create_downloader()
{
    return std::make_unique<downloader_system_curl>();
}
