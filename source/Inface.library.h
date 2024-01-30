#ifndef __INFACE_LIBRARY_H__
#define __INFACE_LIBRARY_H__

#include <Windows.h>
#include <string>

class global
{
public:
    inline static HINSTANCE library = nullptr;
};

inline auto load_impl(const std::string &path)
{
    return LoadLibraryA(path.c_str());
}

inline bool free_impl(HMODULE handle)
{
    return FreeLibrary(handle);
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
