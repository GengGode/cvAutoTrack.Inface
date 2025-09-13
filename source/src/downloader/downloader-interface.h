#pragma once
#include <cvautotrack-error.h>
#include <functional>
#include <memory>
#include <string>

struct downloader_interface
{
    virtual ~downloader_interface() = 0;

    virtual opt_err download_url(const std::string& url, std::string& content) = 0;
    virtual opt_err download_file(const std::string& url, const std::string& to_file) = 0;
    virtual opt_err download_file(const std::string& url, const std::string& to_file, std::function<void(int /*current*/, int /*total*/)> progress) = 0;
};
inline downloader_interface::~downloader_interface() {}

std::unique_ptr<downloader_interface> create_downloader();