#pragma once
#include <cvautotrack-error.h>
#include <functional>
#include <memory>
#include <string>

struct decompressor_interface
{
    virtual ~decompressor_interface() = 0;

    virtual opt_err unzip_file(const std::string& zip_file, const std::string& to_dir) = 0;
    virtual opt_err unzip_file(const std::string& zip_file, const std::string& to_dir, std::function<void(int /*current*/, int /*total*/)> progress) = 0;
    virtual opt_err unzip_file(const std::string& zip_file, std::string& out_file_content) = 0;
    virtual opt_err get_file_md5(const std::string& file, std::string& md5) = 0;
};
inline decompressor_interface::~decompressor_interface() {}

std::unique_ptr<decompressor_interface> create_decompressor();