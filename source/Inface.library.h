#ifndef __INFACE_LIBRARY_H__
#define __INFACE_LIBRARY_H__
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <string>

class global
{
public:
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    inline static HINSTANCE library = nullptr;
#else
    inline static void *library = nullptr;
#endif
};

inline auto load_impl(const std::string &path)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    return LoadLibraryA(path.c_str());
#else
    return dlopen(path.c_str(), RTLD_LAZY);
#endif
}

inline bool free_impl(void *handle)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    return FreeLibrary(handle);
#else
    return dlclose(handle);
#endif
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
    if (try_load_impl("cvAutoTrack.dll"))
        return true;
    return false;
}

#endif // __INFACE_LIBRARY_H__
