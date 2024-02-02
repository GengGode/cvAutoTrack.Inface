#ifndef CVAUTOTRACE_INFACE_H
#define CVAUTOTRACE_INFACE_H

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#ifdef CVAUTOTRACE_INFACE_EXPORTS
#define CVAUTOTRACE_INFACE_API __declspec(dllexport)
#else
#define CVAUTOTRACE_INFACE_API __declspec(dllimport)
#endif
#elif __GNUC__ >= 4
#define CVAUTOTRACE_INFACE_API __attribute__((visibility("default")))
#else
#define CVAUTOTRACE_INFACE_API
#endif

#ifndef explicit_link

#if __cplusplus
extern "C"
{
#endif

    // string alloc
    struct inface_string;
    typedef struct inface_string *inface_string_ptr;

    // string alloc and free
    CVAUTOTRACE_INFACE_API inface_string_ptr alloc_string();
    CVAUTOTRACE_INFACE_API int get_string_length(inface_string_ptr str);
    CVAUTOTRACE_INFACE_API int get_string_context(inface_string_ptr str, char *buffer, int buffer_size);
    CVAUTOTRACE_INFACE_API void free_string(inface_string_ptr str);

    // error code
    CVAUTOTRACE_INFACE_API int get_last_error();
    CVAUTOTRACE_INFACE_API int get_error_define_count();
    CVAUTOTRACE_INFACE_API int get_error_define(int index, inface_string_ptr result);

    // check cvAutoTrace.dll is valid
    CVAUTOTRACE_INFACE_API bool check_impl_valid();
    // get cvAutoTrace.dll version
    CVAUTOTRACE_INFACE_API int auto_init_impl();

    // get callback count
    CVAUTOTRACE_INFACE_API int get_task_callback_count();
    // get callback name
    CVAUTOTRACE_INFACE_API int get_task_callback_name(int index, inface_string_ptr result);
    // install callback
    CVAUTOTRACE_INFACE_API int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/));
    // remove callback
    CVAUTOTRACE_INFACE_API int remove_task_callback(const char *task_name);

    // proxy for cvAutoTrace.dll
    CVAUTOTRACE_INFACE_API bool api(const char *json, inface_string_ptr result);

    CVAUTOTRACE_INFACE_API bool GetTransformOfMap(double &x, double &y, double &a, int &mapId);
    CVAUTOTRACE_INFACE_API bool GetPositionOfMap(double &x, double &y, int &mapId);
    CVAUTOTRACE_INFACE_API bool GetDirection(double &a);
    CVAUTOTRACE_INFACE_API bool GetRotation(double &a);
    CVAUTOTRACE_INFACE_API bool GetStar(double &x, double &y, bool &isEnd);
    CVAUTOTRACE_INFACE_API bool GetStarJson(char *json_buff, int buff_size);
    CVAUTOTRACE_INFACE_API bool GetUID(int &uid);
    CVAUTOTRACE_INFACE_API bool GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid);
#if __cplusplus
}
#endif

#else // explicit_link

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <Windows.h>
#define library_handle_t HMODULE
#define load_lib(path) LoadLibrary(path.c_str())
#define free_lib(lib) FreeLibrary(lib)
#define get_proc(lib, name) GetProcAddress(lib, name)
#else
#include <dlfcn.h>
#define library_handle_t void *
#define load_lib(path) dlopen(path.c_str(), RTLD_LAZY)
#define free_lib(lib) dlclose(lib)
#define get_proc(lib, name) dlsym(lib, name)
#endif
#include <string>
#include <memory>
#include <functional>

struct inface_string;
typedef struct inface_string *inface_string_ptr;

typedef inface_string_ptr (*alloc_string_t)();
typedef int (*get_string_length_t)(inface_string_ptr str);
typedef int (*get_string_context_t)(inface_string_ptr str, char *buffer, int buffer_size);
typedef void (*free_string_t)(inface_string_ptr str);
typedef int (*get_last_error_t)();
typedef int (*get_error_define_count_t)();
typedef int (*get_error_define_t)(int index, inface_string_ptr result);
typedef bool (*check_impl_valid_t)();
typedef int (*auto_init_impl_t)();

typedef bool (*get_task_callback_count_t)();
typedef bool (*get_task_callback_name_t)(int index, inface_string_ptr result);
typedef bool (*install_task_callback_t)(const char *task_name, int (*callback)(const char * /*json*/));
typedef bool (*remove_task_callback_t)(const char *task_name);

typedef bool (*GetTransformOfMap_t)(double &x, double &y, double &a, int &mapId);
typedef bool (*GetPositionOfMap_t)(double &x, double &y, int &mapId);
typedef bool (*GetDirection_t)(double &a);
typedef bool (*GetRotation_t)(double &a);
typedef bool (*GetStar_t)(double &x, double &y, bool &isEnd);
typedef bool (*GetStarJson_t)(char *json_buff, int buff_size);
typedef bool (*GetUID_t)(int &uid);
typedef bool (*GetAllInfo_t)(double &x, double &y, int &mapId, double &a, double &r, int &uid);

struct inface
{
    library_handle_t lib;
    bool is_valid = false;

    alloc_string_t alloc_string_func;
    get_string_length_t get_string_length_func;
    get_string_context_t get_string_context_func;
    free_string_t free_string_func;
    get_last_error_t get_last_error_func;
    get_error_define_count_t get_error_define_count_func;
    get_error_define_t get_error_define_func;
    check_impl_valid_t check_impl_valid_func;
    auto_init_impl_t auto_init_impl_func;

    get_task_callback_count_t get_task_callback_count_func;
    get_task_callback_name_t get_task_callback_name_func;
    install_task_callback_t install_task_callback_func;
    remove_task_callback_t remove_task_callback_func;

    GetTransformOfMap_t GetTransformOfMap_func;
    GetPositionOfMap_t GetPositionOfMap_func;
    GetDirection_t GetDirection_func;
    GetRotation_t GetRotation_func;
    GetStar_t GetStar_func;
    GetStarJson_t GetStarJson_func;
    GetUID_t GetUID_func;
    GetAllInfo_t GetAllInfo_func;

    inface(std::string path = "cvAutoTrack.Inface.dll")
    {
        lib = load_lib(path);
        if (lib == nullptr)
            return;
        is_valid = true;

        alloc_string_func = (alloc_string_t)get_proc(lib, "alloc_string");
        get_string_length_func = (get_string_length_t)get_proc(lib, "get_string_length");
        get_string_context_func = (get_string_context_t)get_proc(lib, "get_string_context");
        free_string_func = (free_string_t)get_proc(lib, "free_string");
        get_last_error_func = (get_last_error_t)get_proc(lib, "get_last_error");
        get_error_define_count_func = (get_error_define_count_t)get_proc(lib, "get_error_define_count");
        get_error_define_func = (get_error_define_t)get_proc(lib, "get_error_define");
        check_impl_valid_func = (check_impl_valid_t)get_proc(lib, "check_impl_valid");
        auto_init_impl_func = (auto_init_impl_t)get_proc(lib, "auto_init_impl");

        get_task_callback_count_func = (get_task_callback_count_t)get_proc(lib, "get_task_callback_count");
        get_task_callback_name_func = (get_task_callback_name_t)get_proc(lib, "get_task_callback_name");
        install_task_callback_func = (install_task_callback_t)get_proc(lib, "install_task_callback");
        remove_task_callback_func = (remove_task_callback_t)get_proc(lib, "remove_task_callback");

        GetTransformOfMap_func = (GetTransformOfMap_t)get_proc(lib, "GetTransformOfMap");
        GetPositionOfMap_func = (GetPositionOfMap_t)get_proc(lib, "GetPositionOfMap");
        GetDirection_func = (GetDirection_t)get_proc(lib, "GetDirection");
        GetRotation_func = (GetRotation_t)get_proc(lib, "GetRotation");
        GetStar_func = (GetStar_t)get_proc(lib, "GetStar");
        GetStarJson_func = (GetStarJson_t)get_proc(lib, "GetStarJson");
        GetUID_func = (GetUID_t)get_proc(lib, "GetUID");
        GetAllInfo_func = (GetAllInfo_t)get_proc(lib, "GetAllInfo");
    }
    ~inface()
    {
        if (lib != nullptr)
            free_lib(lib);
    }

    inface_string_ptr alloc_string()
    {
        if (alloc_string_func == nullptr)
            return nullptr;
        return alloc_string_func();
    }
    int get_string_length(inface_string_ptr str)
    {
        if (get_string_length_func == nullptr)
            return 0;
        return get_string_length_func(str);
    }
    int get_string_context(inface_string_ptr str, char *buffer, int buffer_size)
    {
        if (get_string_context_func == nullptr)
            return 0;
        return get_string_context_func(str, buffer, buffer_size);
    }
    void free_string(inface_string_ptr str)
    {
        if (free_string_func == nullptr)
            return;
        free_string_func(str);
    }
    int get_last_error()
    {
        if (get_last_error_func == nullptr)
            return 0;
        return get_last_error_func();
    }
    int get_error_define_count()
    {
        if (get_error_define_count_func == nullptr)
            return 0;
        return get_error_define_count_func();
    }
    int get_error_define(int index, inface_string_ptr result)
    {
        if (get_error_define_func == nullptr)
            return 0;
        return get_error_define_func(index, result);
    }
    bool check_impl_valid()
    {
        if (check_impl_valid_func == nullptr)
            return false;
        return check_impl_valid_func();
    }
    int auto_init_impl()
    {
        if (auto_init_impl_func == nullptr)
            return 0;
        return auto_init_impl_func();
    }

    int get_task_callback_count()
    {
        if (get_task_callback_count_func == nullptr)
            return 0;
        return get_task_callback_count_func();
    }
    int get_task_callback_name(int index, inface_string_ptr result)
    {
        if (get_task_callback_name_func == nullptr)
            return 0;
        return get_task_callback_name_func(index, result);
    }
    int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/))
    {
        if (install_task_callback_func == nullptr)
            return 0;
        return install_task_callback_func(task_name, callback);
    }
    int remove_task_callback(const char *task_name)
    {
        if (remove_task_callback_func == nullptr)
            return 0;
        return remove_task_callback_func(task_name);
    }

    bool GetTransformOfMap(double &x, double &y, double &a, int &mapId)
    {
        if (GetTransformOfMap_func == nullptr)
            return false;
        return GetTransformOfMap_func(x, y, a, mapId);
    }

    bool GetPositionOfMap(double &x, double &y, int &mapId)
    {
        if (GetPositionOfMap_func == nullptr)
            return false;
        return GetPositionOfMap_func(x, y, mapId);
    }

    bool GetDirection(double &a)
    {
        if (GetDirection_func == nullptr)
            return false;
        return GetDirection_func(a);
    }

    bool GetRotation(double &a)
    {
        if (GetRotation_func == nullptr)
            return false;
        return GetRotation_func(a);
    }

    bool GetStar(double &x, double &y, bool &isEnd)
    {
        if (GetStar_func == nullptr)
            return false;
        return GetStar_func(x, y, isEnd);
    }

    bool GetStarJson(char *json_buff, int buff_size)
    {
        if (GetStarJson_func == nullptr)
            return false;
        return GetStarJson_func(json_buff, buff_size);
    }

    bool GetUID(int &uid)
    {
        if (GetUID_func == nullptr)
            return false;
        return GetUID_func(uid);
    }

    bool GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid)
    {
        if (GetAllInfo_func == nullptr)
            return false;
        return GetAllInfo_func(x, y, mapId, a, r, uid);
    }

    std::string get_error_define(int index)
    {
        auto alloc_res = alloc_string();
        auto get_error_define_res = get_error_define(index, alloc_res);
        auto get_string_length_res = get_string_length(alloc_res);
        char buffer[1024] = {0};
        auto get_string_context_res = get_string_context(alloc_res, buffer, sizeof(buffer));
        std::string result = buffer;
        free_string(alloc_res);
        return result;
    }
    std::string get_task_callback_name(int index)
    {
        auto alloc_res = alloc_string();
        auto get_task_callback_name_res = get_task_callback_name(index, alloc_res);
        auto get_string_length_res = get_string_length(alloc_res);
        char buffer[1024] = {0};
        auto get_string_context_res = get_string_context(alloc_res, buffer, sizeof(buffer));
        std::string result = buffer;
        free_string(alloc_res);
        return result;
    }
};

#endif // explicit_link

#endif // CVAUTOTRACE_INFACE_H
