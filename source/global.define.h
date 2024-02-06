#ifndef __GLOBAL_DEFINE_H__
#define __GLOBAL_DEFINE_H__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <windows.h>
#define pipe_t HANDLE
#define popen _popen
#define pclose _pclose
#define library_handle_t HMODULE
#define load_lib(path) LoadLibrary(path.c_str())
#define free_lib(lib) FreeLibrary(lib)
#define get_proc(lib, name) GetProcAddress(lib, name)
#else
#include <unistd.h>
#include <dlfcn.h>
#define library_handle_t void *
#define load_lib(path) dlopen(path.c_str(), RTLD_LAZY)
#define free_lib(lib) dlclose(lib)
#define get_proc(lib, name) dlsym(lib, name)
#endif

#include <string>
#include <filesystem>

static std::string get_command_result(const std::string &command)
{
    std::string result;
    FILE *fp = popen(command.c_str(), "r");
    if (fp == nullptr)
        return result;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        result += buffer;
    }
    pclose(fp);
    return result;
}

#endif // __GLOBAL_DEFINE_H__