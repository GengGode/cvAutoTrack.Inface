#include <string>
// #include <spdlog/spdlog.h>

// string alloc
struct inface_string
{
    std::string string;
    bool is_valid = true;
};
typedef struct inface_string *inface_string_ptr;

// string alloc and free
inface_string_ptr alloc_string()
{
    return new inface_string();
}

void free_string(inface_string_ptr str)
{
    if (str == nullptr)
        return;
    if (str->is_valid)
        delete str;
}