#ifndef __INFACE_DEFINE_H__
#define __INFACE_DEFINE_H__
#include <string>

// string alloc
struct inface_string
{
    std::string context;
    bool is_valid = true;
};
typedef struct inface_string *inface_string_ptr;

// string alloc and free
inface_string_ptr alloc_string()
{
    return new inface_string();
}

int get_string_length(inface_string_ptr str)
{
    if (str == nullptr)
        return 0;
    return str->context.length();
}
int get_string_context(inface_string_ptr str, char *buffer, int buffer_size)
{
    if (str == nullptr)
        return 0;
    if (buffer == nullptr)
        return 0;
    if (buffer_size <= 0)
        return 0;
    auto length = str->context.length();
    if (length >= buffer_size)
        return 0;
    memcpy(buffer, str->context.c_str(), length);
    return length;
}
void free_string(inface_string_ptr ptr)
{
    if (ptr == nullptr)
        return;
    delete ptr;
}

#endif // __INFACE_DEFINE_H__
