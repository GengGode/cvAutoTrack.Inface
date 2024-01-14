#include "cvAutoTrack.Inface.h"
#include "Inface.library.h"

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
    return func(x, y, mapId);
}
bool GetDirection(double &a)
{
    auto func = (decltype(&GetDirection))GetProcAddress(get_global_handle(), "GetDirection");
    return func(a);
}
bool GetRotation(double &a)
{
    auto func = (decltype(&GetRotation))GetProcAddress(get_global_handle(), "GetRotation");
    return func(a);
}
bool GetStar(double &x, double &y, bool &isEnd)
{
    auto func = (decltype(&GetStar))GetProcAddress(get_global_handle(), "GetStar");
    return func(x, y, isEnd);
}
bool GetStarJson(char *json_buff, int buff_size)
{
    auto func = (decltype(&GetStarJson))GetProcAddress(get_global_handle(), "GetStarJson");
    return func(json_buff, buff_size);
}
bool GetUID(int &uid)
{
    auto func = (decltype(&GetUID))GetProcAddress(get_global_handle(), "GetUID");
    return func(uid);
}
bool GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid)
{
    auto func = (decltype(&GetAllInfo))GetProcAddress(get_global_handle(), "GetAllInfo");
    return func(x, y, mapId, a, r, uid);
}