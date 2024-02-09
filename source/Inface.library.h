#ifndef __INFACE_LIBRARY_H__
#define __INFACE_LIBRARY_H__

#include "global.define.h"

class global
{
public:
    inline static library_handle_t library = nullptr;
};

inline void set_deps_path(const std::string &path)
{
    set_dll_path(path);
}

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

inline std::string get_dll_file_version(const std::string &path)
{
    DWORD dwDummy;
    DWORD dwFVISize = GetFileVersionInfoSizeA(path.c_str(), &dwDummy);
    if (dwFVISize == 0)
        return "";
    std::vector<BYTE> vData(dwFVISize);
    if (!GetFileVersionInfoA(path.c_str(), 0, dwFVISize, &vData[0]))
        return "";
    LPVOID lpBuffer;
    UINT uLen;
    if (!VerQueryValueA(&vData[0], "\\", &lpBuffer, &uLen))
        return "";
    VS_FIXEDFILEINFO *pFileInfo = (VS_FIXEDFILEINFO *)lpBuffer;
    if (pFileInfo->dwSignature != 0xfeef04bd)
        return "";
    std::string version = std::to_string((pFileInfo->dwFileVersionMS >> 16) & 0xffff) + "." + std::to_string((pFileInfo->dwFileVersionMS >> 0) & 0xffff) + "." + std::to_string((pFileInfo->dwFileVersionLS >> 16) & 0xffff); // + "." + std::to_string((pFileInfo->dwFileVersionLS >> 0) & 0xffff);
    return version;
}

#endif // __INFACE_LIBRARY_H__
