#pragma once
#include <memory>
#include <string>

struct configer_interface
{
    virtual ~configer_interface() = default;

    virtual bool load_memory(const std::string& content) = 0;
    virtual bool load_config(const std::string& path) = 0;

    virtual std::string get(const char* key, const char* def_val = "") = 0;
    virtual void set(const char* key, const char* val) = 0;
};

std::unique_ptr<configer_interface> create_configer();
