#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

inface_string_ptr alloc_string()
{
    return new inface_string();
}

int get_string_length(inface_string_ptr str, int *length)
{
    if (str == nullptr)
        return error("字符串指针为空");
    if (length == nullptr)
        return error("长度指针为空");
    *length = str->context.length();
    return 0;
}

int get_string_context(inface_string_ptr str, char *buffer, int buffer_size)
{
    if (str == nullptr)
        return error("字符串指针为空");
    if (buffer == nullptr)
        return error("缓冲区指针为空");
    if (buffer_size <= 0)
        return error("缓冲区大小小于等于0");
    auto length = str->context.length();
    if (length >= buffer_size)
        return error("缓冲区大小不足");
    std::copy(str->context.c_str(), str->context.c_str() + (length > buffer_size ? buffer_size : length), buffer);
    return length;
}

int set_string_context(inface_string_ptr str, const char *buffer, int buffer_size)
{
    if (str == nullptr)
        return error("字符串指针为空");
    if (buffer == nullptr)
        return error("缓冲区指针为空");
    if (buffer_size <= 0)
        return error("缓冲区大小小于等于0");
    str->context = std::string(buffer, buffer_size);
    return buffer_size;
}

void free_string(inface_string_ptr ptr)
{
    if (ptr == nullptr)
        return;
    delete ptr;
}
