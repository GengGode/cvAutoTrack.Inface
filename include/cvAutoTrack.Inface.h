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

    /****************************************************************************************************/
    __declspec(deprecated("** this is a deprecated function, your should used GetCompileVersion**")) extern "C" bool CVAUTOTRACE_INFACE_API verison(char *versionBuff);
    extern "C" bool CVAUTOTRACE_INFACE_API init();
    extern "C" bool CVAUTOTRACE_INFACE_API uninit();

    extern "C" bool CVAUTOTRACE_INFACE_API startServe();
    extern "C" bool CVAUTOTRACE_INFACE_API stopServe();

    extern "C" bool CVAUTOTRACE_INFACE_API SetUseBitbltCaptureMode();
    extern "C" bool CVAUTOTRACE_INFACE_API SetUseDx11CaptureMode();
    extern "C" bool CVAUTOTRACE_INFACE_API SetHandle(long long int handle);
    extern "C" bool CVAUTOTRACE_INFACE_API SetWorldCenter(double x, double y);
    extern "C" bool CVAUTOTRACE_INFACE_API SetWorldScale(double scale);

    extern "C" bool CVAUTOTRACE_INFACE_API ImportMapBlock(int id_x, int id_y, const char *image_data, int image_data_size, int image_width, int image_height);
    extern "C" bool CVAUTOTRACE_INFACE_API ImportMapBlockCenter(int x, int y);
    extern "C" bool CVAUTOTRACE_INFACE_API ImportMapBlockCenterScale(int x, int y, double scale);

    extern "C" bool CVAUTOTRACE_INFACE_API GetTransformOfMap(double &x, double &y, double &a, int &mapId);
    extern "C" bool CVAUTOTRACE_INFACE_API GetPositionOfMap(double &x, double &y, int &mapId);
    extern "C" bool CVAUTOTRACE_INFACE_API GetDirection(double &a);
    extern "C" bool CVAUTOTRACE_INFACE_API GetRotation(double &a);
    extern "C" bool CVAUTOTRACE_INFACE_API GetStar(double &x, double &y, bool &isEnd);
    extern "C" bool CVAUTOTRACE_INFACE_API GetStarJson(char *jsonBuff);
    extern "C" bool CVAUTOTRACE_INFACE_API GetUID(int &uid);
    extern "C" bool CVAUTOTRACE_INFACE_API GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid);

    extern "C" bool CVAUTOTRACE_INFACE_API GetInfoLoadPicture(char *path, int &uid, double &x, double &y, double &a);
    extern "C" bool CVAUTOTRACE_INFACE_API GetInfoLoadVideo(char *path, char *pathOutFile);

    extern "C" bool CVAUTOTRACE_INFACE_API DebugCapture();
    extern "C" bool CVAUTOTRACE_INFACE_API DebugCapturePath(const char *path_buff, int buff_size);

    extern "C" int CVAUTOTRACE_INFACE_API GetLastErr();
    extern "C" int CVAUTOTRACE_INFACE_API GetLastErrMsg(char *msg_buff, int buff_size);
    extern "C" int CVAUTOTRACE_INFACE_API GetLastErrJson(char *json_buff, int buff_size);

    extern "C" bool CVAUTOTRACE_INFACE_API SetDisableFileLog();
    extern "C" bool CVAUTOTRACE_INFACE_API SetEnableFileLog();

    extern "C" bool CVAUTOTRACE_INFACE_API GetCompileVersion(char *version_buff, int buff_size);
    extern "C" bool CVAUTOTRACE_INFACE_API GetCompileTime(char *time_buff, int buff_size);
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

/****************************************************************************************************/
typedef bool (*verison_t)(char *versionBuff);
typedef bool (*init_t)();
typedef bool (*uninit_t)();
typedef bool (*startServe_t)();
typedef bool (*stopServe_t)();
typedef bool (*SetUseBitbltCaptureMode_t)();
typedef bool (*SetUseDx11CaptureMode_t)();
typedef bool (*SetHandle_t)(long long int handle);
typedef bool (*SetWorldCenter_t)(double x, double y);
typedef bool (*SetWorldScale_t)(double scale);
typedef bool (*ImportMapBlock_t)(int id_x, int id_y, const char *image_data, int image_data_size, int image_width, int image_height);
typedef bool (*ImportMapBlockCenter_t)(int x, int y);
typedef bool (*ImportMapBlockCenterScale_t)(int x, int y, double scale);
typedef bool (*GetTransformOfMap_t)(double &x, double &y, double &a, int &mapId);
typedef bool (*GetPositionOfMap_t)(double &x, double &y, int &mapId);
typedef bool (*GetDirection_t)(double &a);
typedef bool (*GetRotation_t)(double &a);
typedef bool (*GetStar_t)(double &x, double &y, bool &isEnd);
typedef bool (*GetStarJson_t)(char *jsonBuff);
typedef bool (*GetUID_t)(int &uid);
typedef bool (*GetAllInfo_t)(double &x, double &y, int &mapId, double &a, double &r, int &uid);
typedef bool (*GetInfoLoadPicture_t)(char *path, int &uid, double &x, double &y, double &a);
typedef bool (*GetInfoLoadVideo_t)(char *path, char *pathOutFile);
typedef bool (*DebugCapture_t)();
typedef bool (*DebugCapturePath_t)(const char *path_buff, int buff_size);
typedef int (*GetLastErr_t)();
typedef int (*GetLastErrMsg_t)(char *msg_buff, int buff_size);
typedef int (*GetLastErrJson_t)(char *json_buff, int buff_size);
typedef bool (*SetDisableFileLog_t)();
typedef bool (*SetEnableFileLog_t)();
typedef bool (*GetCompileVersion_t)(char *version_buff, int buff_size);
typedef bool (*GetCompileTime_t)(char *time_buff, int buff_size);

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

    /****************************************************************************************************/
    verison_t verison_func;
    init_t init_func;
    uninit_t uninit_func;
    startServe_t startServe_func;
    stopServe_t stopServe_func;
    SetUseBitbltCaptureMode_t SetUseBitbltCaptureMode_func;
    SetUseDx11CaptureMode_t SetUseDx11CaptureMode_func;
    SetHandle_t SetHandle_func;
    SetWorldCenter_t SetWorldCenter_func;
    SetWorldScale_t SetWorldScale_func;
    ImportMapBlock_t ImportMapBlock_func;
    ImportMapBlockCenter_t ImportMapBlockCenter_func;
    ImportMapBlockCenterScale_t ImportMapBlockCenterScale_func;
    GetTransformOfMap_t GetTransformOfMap_func;
    GetPositionOfMap_t GetPositionOfMap_func;
    GetDirection_t GetDirection_func;
    GetRotation_t GetRotation_func;
    GetStar_t GetStar_func;
    GetStarJson_t GetStarJson_func;
    GetUID_t GetUID_func;
    GetAllInfo_t GetAllInfo_func;
    GetInfoLoadPicture_t GetInfoLoadPicture_func;
    GetInfoLoadVideo_t GetInfoLoadVideo_func;
    DebugCapture_t DebugCapture_func;
    DebugCapturePath_t DebugCapturePath_func;
    GetLastErr_t GetLastErr_func;
    GetLastErrMsg_t GetLastErrMsg_func;
    GetLastErrJson_t GetLastErrJson_func;
    SetDisableFileLog_t SetDisableFileLog_func;
    SetEnableFileLog_t SetEnableFileLog_func;
    GetCompileVersion_t GetCompileVersion_func;
    GetCompileTime_t GetCompileTime_func;

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
        /****************************************************************************************************/
        verison_func = (verison_t)get_proc(lib, "verison");
        init_func = (init_t)get_proc(lib, "init");
        uninit_func = (uninit_t)get_proc(lib, "uninit");
        startServe_func = (startServe_t)get_proc(lib, "startServe");
        stopServe_func = (stopServe_t)get_proc(lib, "stopServe");
        SetUseBitbltCaptureMode_func = (SetUseBitbltCaptureMode_t)get_proc(lib, "SetUseBitbltCaptureMode");
        SetUseDx11CaptureMode_func = (SetUseDx11CaptureMode_t)get_proc(lib, "SetUseDx11CaptureMode");
        SetHandle_func = (SetHandle_t)get_proc(lib, "SetHandle");
        SetWorldCenter_func = (SetWorldCenter_t)get_proc(lib, "SetWorldCenter");
        SetWorldScale_func = (SetWorldScale_t)get_proc(lib, "SetWorldScale");
        ImportMapBlock_func = (ImportMapBlock_t)get_proc(lib, "ImportMapBlock");
        ImportMapBlockCenter_func = (ImportMapBlockCenter_t)get_proc(lib, "ImportMapBlockCenter");
        ImportMapBlockCenterScale_func = (ImportMapBlockCenterScale_t)get_proc(lib, "ImportMapBlockCenterScale");
        GetTransformOfMap_func = (GetTransformOfMap_t)get_proc(lib, "GetTransformOfMap");
        GetPositionOfMap_func = (GetPositionOfMap_t)get_proc(lib, "GetPositionOfMap");
        GetDirection_func = (GetDirection_t)get_proc(lib, "GetDirection");
        GetRotation_func = (GetRotation_t)get_proc(lib, "GetRotation");
        GetStar_func = (GetStar_t)get_proc(lib, "GetStar");
        GetStarJson_func = (GetStarJson_t)get_proc(lib, "GetStarJson");
        GetUID_func = (GetUID_t)get_proc(lib, "GetUID");
        GetAllInfo_func = (GetAllInfo_t)get_proc(lib, "GetAllInfo");
        GetInfoLoadPicture_func = (GetInfoLoadPicture_t)get_proc(lib, "GetInfoLoadPicture");
        GetInfoLoadVideo_func = (GetInfoLoadVideo_t)get_proc(lib, "GetInfoLoadVideo");
        DebugCapture_func = (DebugCapture_t)get_proc(lib, "DebugCapture");
        DebugCapturePath_func = (DebugCapturePath_t)get_proc(lib, "DebugCapturePath");
        GetLastErr_func = (GetLastErr_t)get_proc(lib, "GetLastErr");
        GetLastErrMsg_func = (GetLastErrMsg_t)get_proc(lib, "GetLastErrMsg");
        GetLastErrJson_func = (GetLastErrJson_t)get_proc(lib, "GetLastErrJson");
        SetDisableFileLog_func = (SetDisableFileLog_t)get_proc(lib, "SetDisableFileLog");
        SetEnableFileLog_func = (SetEnableFileLog_t)get_proc(lib, "SetEnableFileLog");
        GetCompileVersion_func = (GetCompileVersion_t)get_proc(lib, "GetCompileVersion");
        GetCompileTime_func = (GetCompileTime_t)get_proc(lib, "GetCompileTime");
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

    /****************************************************************************************************/

    bool verison(char *versionBuff)
    {
        if (verison_func == nullptr)
            return false;
        return verison_func(versionBuff);
    }
    bool init()
    {
        if (init_func == nullptr)
            return false;
        return init_func();
    }
    bool uninit()
    {
        if (uninit_func == nullptr)
            return false;
        return uninit_func();
    }
    bool startServe()
    {
        if (startServe_func == nullptr)
            return false;
        return startServe_func();
    }
    bool stopServe()
    {
        if (stopServe_func == nullptr)
            return false;
        return stopServe_func();
    }
    bool SetUseBitbltCaptureMode()
    {
        if (SetUseBitbltCaptureMode_func == nullptr)
            return false;
        return SetUseBitbltCaptureMode_func();
    }
    bool SetUseDx11CaptureMode()
    {
        if (SetUseDx11CaptureMode_func == nullptr)
            return false;
        return SetUseDx11CaptureMode_func();
    }
    bool SetHandle(long long int handle)
    {
        if (SetHandle_func == nullptr)
            return false;
        return SetHandle_func(handle);
    }
    bool SetWorldCenter(double x, double y)
    {
        if (SetWorldCenter_func == nullptr)
            return false;
        return SetWorldCenter_func(x, y);
    }
    bool SetWorldScale(double scale)
    {
        if (SetWorldScale_func == nullptr)
            return false;
        return SetWorldScale_func(scale);
    }
    bool ImportMapBlock(int id_x, int id_y, const char *image_data, int image_data_size, int image_width, int image_height)
    {
        if (ImportMapBlock_func == nullptr)
            return false;
        return ImportMapBlock_func(id_x, id_y, image_data, image_data_size, image_width, image_height);
    }
    bool ImportMapBlockCenter(int x, int y)
    {
        if (ImportMapBlockCenter_func == nullptr)
            return false;
        return ImportMapBlockCenter_func(x, y);
    }
    bool ImportMapBlockCenterScale(int x, int y, double scale)
    {
        if (ImportMapBlockCenterScale_func == nullptr)
            return false;
        return ImportMapBlockCenterScale_func(x, y, scale);
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
    bool GetStarJson(char *jsonBuff)
    {
        if (GetStarJson_func == nullptr)
            return false;
        return GetStarJson_func(jsonBuff);
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
    bool GetInfoLoadPicture(char *path, int &uid, double &x, double &y, double &a)
    {
        if (GetInfoLoadPicture_func == nullptr)
            return false;
        return GetInfoLoadPicture_func(path, uid, x, y, a);
    }
    bool GetInfoLoadVideo(char *path, char *pathOutFile)
    {
        if (GetInfoLoadVideo_func == nullptr)
            return false;
        return GetInfoLoadVideo_func(path, pathOutFile);
    }
    bool DebugCapture()
    {
        if (DebugCapture_func == nullptr)
            return false;
        return DebugCapture_func();
    }
    bool DebugCapturePath(const char *path_buff, int buff_size)
    {
        if (DebugCapturePath_func == nullptr)
            return false;
        return DebugCapturePath_func(path_buff, buff_size);
    }
    int GetLastErr()
    {
        if (GetLastErr_func == nullptr)
            return -1;
        return GetLastErr_func();
    }
    int GetLastErrMsg(char *msg_buff, int buff_size)
    {
        if (GetLastErrMsg_func == nullptr)
            return -1;
        return GetLastErrMsg_func(msg_buff, buff_size);
    }
    int GetLastErrJson(char *json_buff, int buff_size)
    {
        if (GetLastErrJson_func == nullptr)
            return -1;
        return GetLastErrJson_func(json_buff, buff_size);
    }
    bool SetDisableFileLog()
    {
        if (SetDisableFileLog_func == nullptr)
            return false;
        return SetDisableFileLog_func();
    }
    bool SetEnableFileLog()
    {
        if (SetEnableFileLog_func == nullptr)
            return false;
        return SetEnableFileLog_func();
    }
    bool GetCompileVersion(char *version_buff, int buff_size)
    {
        if (GetCompileVersion_func == nullptr)
            return false;
        return GetCompileVersion_func(version_buff, buff_size);
    }
    bool GetCompileTime(char *time_buff, int buff_size)
    {
        if (GetCompileTime_func == nullptr)
            return false;
        return GetCompileTime_func(time_buff, buff_size);
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
