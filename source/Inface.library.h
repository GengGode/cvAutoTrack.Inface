#ifndef __INFACE_LIBRARY_H__
#define __INFACE_LIBRARY_H__

#include <Windows.h>
#include <string>

auto load_impl(const std::string &path)
{
    return LoadLibraryA(path.c_str());
}

bool free_impl(HMODULE handle)
{
    return FreeLibrary(handle);
}

#endif // __INFACE_LIBRARY_H__
