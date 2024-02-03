#ifndef __INFACE_LIBRARY_H__
#define __INFACE_LIBRARY_H__

#include "global.define.h"

class global
{
public:
    inline static library_handle_t library = nullptr;
};

inline auto load_impl(const std::string &path)
{
    return load_lib(path);
}

inline bool free_impl(library_handle_t handle)
{
    free_lib(handle);
    return true;
}

inline auto get_global_handle()
{
    return global::library;
}

inline bool try_load_impl(const std::string &path)
{
    global::library = load_impl(path);
    return global::library != nullptr;
}

inline bool auto_load_impl(const std::string &path, bool is_reload = false)
{
    if (is_reload && global::library != nullptr)
        free_impl(global::library);
    if (global::library != nullptr)
        return true;
    if (try_load_impl(path))
        return true;
    return false;
}

#endif // __INFACE_LIBRARY_H__
