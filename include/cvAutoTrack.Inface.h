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

#ifdef explicit_link
    #define maroc_concatenate(a, b) maroc_concatenate_1(a, b)
    #define maroc_concatenate_1(a, b) maroc_concatenate_2(a, b)
    #define maroc_concatenate_2(a, b) a##b
    #define maroc_expand(x) x
    #define maroc_for_each_0(pred, ...)
    #define maroc_for_each_1(pred, n, x, ...) pred(x, 0)
    #define maroc_for_each_2(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_1(pred, 1, __VA_ARGS__))
    #define maroc_for_each_3(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_2(pred, 2, __VA_ARGS__))
    #define maroc_for_each_4(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_3(pred, 3, __VA_ARGS__))
    #define maroc_for_each_5(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_4(pred, 4, __VA_ARGS__))
    #define maroc_for_each_6(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_5(pred, 5, __VA_ARGS__))
    #define maroc_for_each_7(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_6(pred, 6, __VA_ARGS__))
    #define maroc_for_each_8(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_7(pred, 7, __VA_ARGS__))
    #define maroc_for_each_9(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_8(pred, 8, __VA_ARGS__))
    #define maroc_for_each_10(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_9(pred, 9, __VA_ARGS__))
    #define maroc_args_count(...) maroc_expand(maroc_arg_count_1(0, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
    #define maroc_arg_count_1(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, n, ...) n
    #define maroc_for_each_(n, pred, ...) maroc_expand(maroc_concatenate(maroc_for_each_, n)(pred, n, __VA_ARGS__))
    #define maroc_for_each(pred, ...) maroc_expand(maroc_for_each_(maroc_expand(maroc_args_count(__VA_ARGS__)), pred, __VA_ARGS__))
    #define comma_0()
    #define comma_1() ,
    #define comma_2() ,
    #define comma_3() ,
    #define comma_4() ,
    #define comma_5() ,
    #define comma_6() ,
    #define comma_7() ,
    #define comma_8() ,
    #define comma_9() ,

    #define ret_bool_false false
    #define ret_int_false -1
    #define ret_void_false

    #define type_null_
    #define type_null_bool
    #define type_null_int
    #define type_null_double
    #define type_null_bool_ref
    #define type_null_int_ref
    #define type_null_double_ref
    #define type_null_long_long_int
    #define type_null_const_char_ptr
    #define type_null_char_ptr
    #define type_null_int_ptr
    #define only_name(v, n) type_null_##v comma_##n()
    #define bind_call(ret_type, name, ...)                       \
        ret_type name(__VA_ARGS__)                               \
        {                                                        \
            auto func = (decltype(&::name))get_proc(lib, #name); \
            if (func == nullptr)                                 \
                return ret_##ret_type##_false;                   \
            return func(maroc_for_each(only_name, __VA_ARGS__)); \
        }

    #if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
        #include <Windows.h>
        #define library_handle_t HMODULE
        #define load_lib(path) LoadLibrary(path.c_str())
        #define free_lib(lib) FreeLibrary(lib)
        #define get_proc(lib, name) GetProcAddress(lib, name)
    #else
        #include <dlfcn.h>
        #define library_handle_t void*
        #define load_lib(path) dlopen(path.c_str(), RTLD_LAZY)
        #define free_lib(lib) dlclose(lib)
        #define get_proc(lib, name) dlsym(lib, name)
    #endif

    #include <functional>
    #include <memory>
    #include <string>

typedef int* int_ptr;
typedef long long int long_long_int;
typedef const char* const_char_ptr;
typedef char* char_ptr;
typedef bool& bool_ref;
typedef int& int_ref;
typedef double& double_ref;

#endif // explicit_link

#if __cplusplus
extern "C"
{
#endif

    // string alloc
    struct inface_string;
    typedef struct inface_string* inface_string_ptr;

    // string alloc and free
    CVAUTOTRACE_INFACE_API inface_string_ptr alloc_string();
    CVAUTOTRACE_INFACE_API int get_string_length(inface_string_ptr str, int* length);
    CVAUTOTRACE_INFACE_API int get_string_context(inface_string_ptr str, char* buffer, int buffer_size);
    CVAUTOTRACE_INFACE_API int set_string_context(inface_string_ptr str, const char* buffer, int buffer_size);
    CVAUTOTRACE_INFACE_API void free_string(inface_string_ptr str);

    // error code
    CVAUTOTRACE_INFACE_API int get_last_error();
    CVAUTOTRACE_INFACE_API int get_error_define_count();
    CVAUTOTRACE_INFACE_API int get_error_define(int index, inface_string_ptr result);

    // check cvAutoTrace.dll is valid
    CVAUTOTRACE_INFACE_API bool check_impl_valid();
    // get cvAutoTrace.dll version
    CVAUTOTRACE_INFACE_API int auto_init_impl();
    // get online core info
    CVAUTOTRACE_INFACE_API int get_online_core_latest_version(inface_string_ptr result);
    CVAUTOTRACE_INFACE_API int get_online_core_version_list(inface_string_ptr result);
    CVAUTOTRACE_INFACE_API int get_online_core_version_info(const char* version, inface_string_ptr result);
    CVAUTOTRACE_INFACE_API int get_local_core_version_list(inface_string_ptr result);

    // inface version info
    CVAUTOTRACE_INFACE_API int get_inface_version(inface_string_ptr result);

    // get callback count
    CVAUTOTRACE_INFACE_API int get_task_callback_count();
    // get callback name
    CVAUTOTRACE_INFACE_API int get_task_callback_name(int index, inface_string_ptr result);
    // install callback
    CVAUTOTRACE_INFACE_API int install_task_callback(const char* task_name, int (*callback)(const char* /*json*/));
    // remove callback
    CVAUTOTRACE_INFACE_API int remove_task_callback(const char* task_name);

    // proxy for cvAutoTrace.dll
    CVAUTOTRACE_INFACE_API bool api(const char* json, inface_string_ptr result);

    /****************************************************************************************************/
    bool CVAUTOTRACE_INFACE_API InitResource();
    bool CVAUTOTRACE_INFACE_API UnInitResource();

    bool CVAUTOTRACE_INFACE_API SetResourceFile(const char* path, const char* config, int config_size);

    bool CVAUTOTRACE_INFACE_API SetCoreCachePath(const char* path);
    bool CVAUTOTRACE_INFACE_API GetCoreCachePath(char* path_buff, int buff_size);

    bool CVAUTOTRACE_INFACE_API startServe();
    bool CVAUTOTRACE_INFACE_API stopServe();

    bool CVAUTOTRACE_INFACE_API SetUseBitbltCaptureMode();
    bool CVAUTOTRACE_INFACE_API SetUseDx11CaptureMode();
    bool CVAUTOTRACE_INFACE_API SetHandle(long long int handle);
    bool CVAUTOTRACE_INFACE_API SetWorldCenter(double x, double y);
    bool CVAUTOTRACE_INFACE_API SetWorldScale(double scale);

    bool CVAUTOTRACE_INFACE_API ImportMapBlock(int id_x, int id_y, const char* image_data, int image_data_size, int image_width, int image_height);
    bool CVAUTOTRACE_INFACE_API ImportMapBlockCenter(int x, int y);
    bool CVAUTOTRACE_INFACE_API ImportMapBlockCenterScale(int x, int y, double scale);

    bool CVAUTOTRACE_INFACE_API GetTransformOfMap(double& x, double& y, double& a, int& mapId);
    bool CVAUTOTRACE_INFACE_API GetPositionOfMap(double& x, double& y, int& mapId);
    bool CVAUTOTRACE_INFACE_API GetDirection(double& a);
    bool CVAUTOTRACE_INFACE_API GetRotation(double& a);
    bool CVAUTOTRACE_INFACE_API GetStar(double& x, double& y, bool& isEnd);
    bool CVAUTOTRACE_INFACE_API GetStarJson(char* jsonBuff);
    bool CVAUTOTRACE_INFACE_API GetUID(int& uid);
    bool CVAUTOTRACE_INFACE_API GetAllInfo(double& x, double& y, int& mapId, double& a, double& r, int& uid);

    bool CVAUTOTRACE_INFACE_API GetInfoLoadPicture(char* path, int& uid, double& x, double& y, double& a);
    bool CVAUTOTRACE_INFACE_API GetInfoLoadVideo(char* path, char* pathOutFile);

    bool CVAUTOTRACE_INFACE_API DebugCapture();
    bool CVAUTOTRACE_INFACE_API DebugCapturePath(const char* path_buff, int buff_size);

    int CVAUTOTRACE_INFACE_API GetLastErr();
    int CVAUTOTRACE_INFACE_API GetLastErrMsg(char* msg_buff, int buff_size);
    int CVAUTOTRACE_INFACE_API GetLastErrJson(char* json_buff, int buff_size);

    bool CVAUTOTRACE_INFACE_API SetDisableFileLog();
    bool CVAUTOTRACE_INFACE_API SetEnableFileLog();

    bool CVAUTOTRACE_INFACE_API GetCompileVersion(char* version_buff, int buff_size);
    bool CVAUTOTRACE_INFACE_API GetCompileTime(char* time_buff, int buff_size);
    bool CVAUTOTRACE_INFACE_API GetCoreModulePath(char* path_buff, int buff_size);

#if __cplusplus
}
#endif

#ifdef explicit_link
// #else // explicit_link

typedef int (*json_callback_ptr)(const char* /*json*/);

    #define type_null_json_callback_ptr
    #define type_null_inface_string_ptr
    #define ret_inface_string_ptr_false nullptr

struct inface
{
    library_handle_t lib;
    bool is_valid = false;

    bind_call(inface_string_ptr, alloc_string);
    bind_call(int, get_string_length, inface_string_ptr str, int_ptr length);
    bind_call(int, get_string_context, inface_string_ptr str, char_ptr buffer, int buffer_size);
    bind_call(int, set_string_context, inface_string_ptr str, const_char_ptr buffer, int buffer_size);
    bind_call(void, free_string, inface_string_ptr str);
    bind_call(int, get_last_error);
    bind_call(int, get_error_define_count);
    bind_call(int, get_error_define, int index, inface_string_ptr result);
    bind_call(bool, check_impl_valid);
    bind_call(int, auto_init_impl);
    bind_call(int, get_online_core_latest_version, inface_string_ptr result);
    bind_call(int, get_online_core_version_list, inface_string_ptr result);
    bind_call(int, get_online_core_version_info, const_char_ptr version, inface_string_ptr result);
    bind_call(int, get_local_core_version_list, inface_string_ptr result);
    bind_call(int, get_inface_version, inface_string_ptr result);
    bind_call(int, get_task_callback_count);
    bind_call(int, get_task_callback_name, int index, inface_string_ptr result);
    bind_call(int, install_task_callback, const_char_ptr task_name, json_callback_ptr callback);
    bind_call(int, remove_task_callback, const_char_ptr task_name);
    bind_call(bool, api, const_char_ptr json, inface_string_ptr result);

    /****************************************************************************************************/
    bind_call(bool, InitResource);
    bind_call(bool, UnInitResource);
    bind_call(bool, SetResourceFile, const_char_ptr path, const_char_ptr config, int config_size);
    bind_call(bool, SetCoreCachePath, const_char_ptr path);
    bind_call(bool, GetCoreCachePath, char_ptr path_buff, int buff_size);
    bind_call(bool, SetWorldCenter, double x, double y);
    bind_call(bool, SetWorldScale, double scale);
    bind_call(bool, GetTransformOfMap, double_ref x, double_ref y, double_ref a, int_ref mapId);
    bind_call(bool, GetPositionOfMap, double_ref x, double_ref y, int_ref mapId);
    bind_call(bool, GetDirection, double_ref a);
    bind_call(bool, GetRotation, double_ref a);
    bind_call(bool, GetUID, int_ref uid);
    bind_call(bool, GetAllInfo, double_ref x, double_ref y, int_ref mapId, double_ref a, double_ref r, int_ref uid);
    bind_call(bool, DebugCapture);
    bind_call(int, GetLastErr);
    bind_call(int, GetLastErrMsg, char_ptr msg_buff, int buff_size);
    bind_call(int, GetLastErrJson, char_ptr json_buff, int buff_size);
    bind_call(bool, GetCompileVersion, char_ptr version_buff, int buff_size);
    bind_call(bool, GetCompileTime, char_ptr time_buff, int buff_size);
    bind_call(bool, GetCoreModulePath, char_ptr time_buff, int buff_size);

    inface(std::string path = "cvAutoTrack.Inface.dll") { lib = load_lib(path); }
    ~inface()
    {
        if (lib != nullptr)
            free_lib(lib);
    }

    std::string to_string(inface_string_ptr str)
    {
        int len = 0;
        auto get_string_length_res = get_string_length(str, &len);
        char* buffer = new char[len + 1]{ 0 };
        auto get_string_context_res = get_string_context(str, buffer, len + 1);
        std::string result = buffer;
        delete[] buffer;
        return result;
    }

    std::string get_error_define(int index)
    {
        int len = 0;
        auto alloc_res = alloc_string();
        auto get_error_define_res = get_error_define(index, alloc_res);
        return to_string(alloc_res);
    }

    std::string get_task_callback_name(int index)
    {
        int len = 0;
        auto alloc_res = alloc_string();
        auto get_task_callback_name_res = get_task_callback_name(index, alloc_res);
        return to_string(alloc_res);
    }
};

#endif // explicit_link

#endif // CVAUTOTRACE_INFACE_H
