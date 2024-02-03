#include "cvAutoTrack.Inface.h"
#include "Inface.library.h"

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#define GetProcAddress GetProcAddress
#else
#define GetProcAddress dlsym
#endif

bool verison(char *versionBuff)
{
    auto func = (decltype(&verison))GetProcAddress(get_global_handle(), "verison");
    if (func == nullptr)
        return false;
    return func(versionBuff);
}
bool init()
{
    auto func = (decltype(&init))GetProcAddress(get_global_handle(), "init");
    if (func == nullptr)
        return false;
    return func();
}
bool uninit()
{
    auto func = (decltype(&uninit))GetProcAddress(get_global_handle(), "uninit");
    if (func == nullptr)
        return false;
    return func();
}
bool startServe()
{
    auto func = (decltype(&startServe))GetProcAddress(get_global_handle(), "startServe");
    if (func == nullptr)
        return false;
    return func();
}
bool stopServe()
{
    auto func = (decltype(&stopServe))GetProcAddress(get_global_handle(), "stopServe");
    if (func == nullptr)
        return false;
    return func();
}
bool SetUseBitbltCaptureMode()
{
    auto func = (decltype(&SetUseBitbltCaptureMode))GetProcAddress(get_global_handle(), "SetUseBitbltCaptureMode");
    if (func == nullptr)
        return false;
    return func();
}
bool SetUseDx11CaptureMode()
{
    auto func = (decltype(&SetUseDx11CaptureMode))GetProcAddress(get_global_handle(), "SetUseDx11CaptureMode");
    if (func == nullptr)
        return false;
    return func();
}
bool SetHandle(long long int handle)
{
    auto func = (decltype(&SetHandle))GetProcAddress(get_global_handle(), "SetHandle");
    if (func == nullptr)
        return false;
    return func(handle);
}
bool SetWorldCenter(double x, double y)
{
    auto func = (decltype(&SetWorldCenter))GetProcAddress(get_global_handle(), "SetWorldCenter");
    if (func == nullptr)
        return false;
    return func(x, y);
}
bool SetWorldScale(double scale)
{
    auto func = (decltype(&SetWorldScale))GetProcAddress(get_global_handle(), "SetWorldScale");
    if (func == nullptr)
        return false;
    return func(scale);
}
bool ImportMapBlock(int id_x, int id_y, const char *image_data, int image_data_size, int image_width, int image_height)
{
    auto func = (decltype(&ImportMapBlock))GetProcAddress(get_global_handle(), "ImportMapBlock");
    if (func == nullptr)
        return false;
    return func(id_x, id_y, image_data, image_data_size, image_width, image_height);
}
bool ImportMapBlockCenter(int x, int y)
{
    auto func = (decltype(&ImportMapBlockCenter))GetProcAddress(get_global_handle(), "ImportMapBlockCenter");
    if (func == nullptr)
        return false;
    return func(x, y);
}
bool ImportMapBlockCenterScale(int x, int y, double scale)
{
    auto func = (decltype(&ImportMapBlockCenterScale))GetProcAddress(get_global_handle(), "ImportMapBlockCenterScale");
    if (func == nullptr)
        return false;
    return func(x, y, scale);
}
bool GetTransformOfMap(double &x, double &y, double &a, int &mapId)
{
    auto func = (decltype(&GetTransformOfMap))GetProcAddress(get_global_handle(), "GetTransformOfMap");
    if (func == nullptr)
        return false;
    return func(x, y, a, mapId);
}
bool GetPositionOfMap(double &x, double &y, int &mapId)
{
    auto func = (decltype(&GetPositionOfMap))GetProcAddress(get_global_handle(), "GetPositionOfMap");
    if (func == nullptr)
        return false;
    return func(x, y, mapId);
}
bool GetDirection(double &a)
{
    auto func = (decltype(&GetDirection))GetProcAddress(get_global_handle(), "GetDirection");
    if (func == nullptr)
        return false;
    return func(a);
}
bool GetRotation(double &a)
{
    auto func = (decltype(&GetRotation))GetProcAddress(get_global_handle(), "GetRotation");
    if (func == nullptr)
        return false;
    return func(a);
}
bool GetStar(double &x, double &y, bool &isEnd)
{
    auto func = (decltype(&GetStar))GetProcAddress(get_global_handle(), "GetStar");
    if (func == nullptr)
        return false;
    return func(x, y, isEnd);
}
bool GetStarJson(char *jsonBuff)
{
    auto func = (decltype(&GetStarJson))GetProcAddress(get_global_handle(), "GetStarJson");
    if (func == nullptr)
        return false;
    return func(jsonBuff);
}
bool GetUID(int &uid)
{
    auto func = (decltype(&GetUID))GetProcAddress(get_global_handle(), "GetUID");
    if (func == nullptr)
        return false;
    return func(uid);
}
bool GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid)
{
    auto func = (decltype(&GetAllInfo))GetProcAddress(get_global_handle(), "GetAllInfo");
    if (func == nullptr)
        return false;
    return func(x, y, mapId, a, r, uid);
}
bool GetInfoLoadPicture(char *path, int &uid, double &x, double &y, double &a)
{
    auto func = (decltype(&GetInfoLoadPicture))GetProcAddress(get_global_handle(), "GetInfoLoadPicture");
    if (func == nullptr)
        return false;
    return func(path, uid, x, y, a);
}
bool GetInfoLoadVideo(char *path, char *pathOutFile)
{
    auto func = (decltype(&GetInfoLoadVideo))GetProcAddress(get_global_handle(), "GetInfoLoadVideo");
    if (func == nullptr)
        return false;
    return func(path, pathOutFile);
}
bool DebugCapture()
{
    auto func = (decltype(&DebugCapture))GetProcAddress(get_global_handle(), "DebugCapture");
    if (func == nullptr)
        return false;
    return func();
}
bool DebugCapturePath(const char *path_buff, int buff_size)
{
    auto func = (decltype(&DebugCapturePath))GetProcAddress(get_global_handle(), "DebugCapturePath");
    if (func == nullptr)
        return false;
    return func(path_buff, buff_size);
}
int GetLastErr()
{
    auto func = (decltype(&GetLastErr))GetProcAddress(get_global_handle(), "GetLastErr");
    if (func == nullptr)
        return -1;
    return func();
}
int GetLastErrMsg(char *msg_buff, int buff_size)
{
    auto func = (decltype(&GetLastErrMsg))GetProcAddress(get_global_handle(), "GetLastErrMsg");
    if (func == nullptr)
        return -1;
    return func(msg_buff, buff_size);
}
int GetLastErrJson(char *json_buff, int buff_size)
{
    auto func = (decltype(&GetLastErrJson))GetProcAddress(get_global_handle(), "GetLastErrJson");
    if (func == nullptr)
        return -1;
    return func(json_buff, buff_size);
}
bool SetDisableFileLog()
{
    auto func = (decltype(&SetDisableFileLog))GetProcAddress(get_global_handle(), "SetDisableFileLog");
    if (func == nullptr)
        return false;
    return func();
}
bool SetEnableFileLog()
{
    auto func = (decltype(&SetEnableFileLog))GetProcAddress(get_global_handle(), "SetEnableFileLog");
    if (func == nullptr)
        return false;
    return func();
}
bool GetCompileVersion(char *version_buff, int buff_size)
{
    auto func = (decltype(&GetCompileVersion))GetProcAddress(get_global_handle(), "GetCompileVersion");
    if (func == nullptr)
        return false;
    return func(version_buff, buff_size);
}
bool GetCompileTime(char *time_buff, int buff_size)
{
    auto func = (decltype(&GetCompileTime))GetProcAddress(get_global_handle(), "GetCompileTime");
    if (func == nullptr)
        return false;
    return func(time_buff, buff_size);
}