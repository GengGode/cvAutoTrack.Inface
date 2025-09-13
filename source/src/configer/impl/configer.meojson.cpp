#include "../configer-interface.h"
#include <meojson/json.hpp>

struct configer_meojson : public configer_interface
{
    json::value root;

    bool load_memory(const std::string& content) override
    {
        try
        {
            auto value = json::parse(content);
            if (!value)
                return false;
            root = std::move(*value);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool load_config(const std::string& path) override
    {
        try
        {
            std::ifstream file(path);
            if (!file.is_open())
                return false;

            std::stringstream buffer;
            buffer << file.rdbuf();
            auto value = json::parse(buffer.str());
            if (!value)
                return false;
            root = std::move(*value);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::string get(const char* key, const char* def_val = "") override
    {
        if (root.contains(key))
            return root[key].format();
        return def_val;
    }

    void set(const char* key, const char* val) override { root[key] = val; }
};

std::unique_ptr<configer_interface> create_configer()
{
    return std::make_unique<configer_meojson>();
}