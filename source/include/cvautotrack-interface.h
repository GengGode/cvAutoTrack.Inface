#ifndef CVAUTOTRACE_INFACE_H
#define CVAUTOTRACE_INFACE_H

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    #ifdef CVAUTOTRACE_INFACE_EXPORTS
        #define CVAUTOTRACE_INFACE_API __declspec(dllexport)
    #else
        #define CVAUTOTRACE_INFACE_API __declspec(dllimport)
    #endif
#endif

#if __cplusplus
extern "C"
{
#endif

#include "cvautotrack-error.h"

    struct string_span
    {
        char* data;
        int size;
    };
    void free_string_span(string_span* span);

    // 版本检查相关接口
    // 两个系列，检查本地可用版本和检查在线可用版本
    // 版本字符串和哈希值

    /// @brief 检查在线可用版本
    /// @return 是否可用
    bool check_online_usable();

    /// @brief 获取本地可用版本列表
    /// @param out_versions 输出版本列表，多个版本以逗号分隔
    /// @return 错误信息，nullptr表示成功
    opt_err get_local_usable_version_list(string_span* out_versions);
    /// @brief 获取在线可用版本列表
    /// @param out_versions 输出版本列表，多个版本以逗号分隔
    /// @return 错误信息，nullptr表示成功
    opt_err get_online_usable_version_list(string_span* out_versions);

    // 签出版本相关接口，签出优先使用本地版本和优先使用在线版本两种方式
    // 签出之后就可以调用 api 接口了
    opt_err checkout_local_version(const char* version);
    opt_err checkout_online_version(const char* version);
    opt_err checkout_version_priority_local(const char* version);
    opt_err checkout_version_priority_online(const char* version);

    /* v1 */

    // 定义上下文结构体
    struct cvAutoTrackContextV1
    {
        // 开发保留接口
        bool (*DebugLoadMapImagePath)(const char* path);

        // 资源管理接口
        bool (*InitResource)();
        bool (*UnInitResource)();

        // 缓存配置接口
        bool (*SetCacheConfig)(const char*, const char*, const char*, int);
        bool (*SetCoreCachePath)(const char*);
        bool (*GetCoreCachePath)(char*, int);

        // 服务控制接口
        bool (*StartServer)();
        bool (*StopServer)();
        bool (*SetServerInterval)(int);
        bool (*SetServerCallback)(void (*)(const char*, int));

        // 日志配置接口
        bool (*SetDisableFileLog)();
        bool (*SetEnableFileLog)();
        bool (*SetLogFilePath)(const char*);
        bool (*SetLogFileName)(const char*);

        // 截图模式配置接口
        bool (*SetUseBitbltCaptureMode)();
        bool (*SetUseGraphicsCaptureMode)();
        bool (*SetUseDwmCaptureMode)();
        bool (*SetUseLocalPictureMode)();
        bool (*SetUseLocalVideoMode)();

        // 采集相关接口
        bool (*SetCaptureHandle)(long long);
        bool (*SetCaptureHandleCallback)(long long (*)());
        bool (*SetScreenSourceCallback)(void (*)(const char*, int&));
        bool (*SetScreenSourceCallbackEx)(void (*)(const char*, int&, int&, int&));
        bool (*SetScreenSourceImage)(const char*, int);
        bool (*SetScreenSourceImageEx)(const char*, int, int, int);
        bool (*SetScreenClientRectCallback)(void (*)(int&, int&, int&, int&));

        // 跟踪缓存接口
        bool (*SetTrackCachePath)(const char*);
        bool (*SetTrackCacheName)(const char*);

        // 坐标配置接口
        bool (*SetWorldCenter)(double, double);
        bool (*SetWorldScale)(double);

        // 数据获取接口
        bool (*GetTransformOfMap)(double&, double&, double&, int&);
        bool (*GetPositionOfMap)(double&, double&, int&);
        bool (*GetDirection)(double&);
        bool (*GetRotation)(double&);
        bool (*GetUID)(int&);
        bool (*GetAllInfo)(double&, double&, int&, double&, double&, int&);

        // 调试接口
        bool (*DebugCapture)();
        bool (*DebugCapturePath)(const char*);

        // 错误处理接口
        int (*GetLastErr)();
        int (*GetLastErrMsg)(char*, int);
        int (*GetLastErrJson)(char*, int);

        // 版本信息接口
        bool (*GetCompileVersion)(char*, int);
        bool (*GetCompileTime)(char*, int);
        bool (*GetCoreModulePath)(char*, int);
    };
    typedef struct cvAutoTrackContextV1* cvAutoTrackContextV1Ptr;

    // 定义上下文初始化函数
    CVAUTOTRACE_INFACE_API cvAutoTrackContextV1* create_cvAutoTrack_context_v1();
    // 定义上下文销毁函数
    CVAUTOTRACE_INFACE_API void destroy_cvAutoTrack_context_v1(cvAutoTrackContextV1* context);
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

#endif // CVAUTOTRACE_INFACE_H
