#ifndef __INFACE_DEFINE_H__
#define __INFACE_DEFINE_H__
#include <string>
#include <map>
#include <functional>

// string alloc
struct inface_string
{
    std::string context;
};
typedef struct inface_string *inface_string_ptr;

// task map
inline static std::map<std::string, std::function<int(std::string)>> inface_task_map = {
    {"download_start", nullptr},
    {"download_progress", nullptr},
    {"download_failed", nullptr},
    {"download_success", nullptr}};
// value map
inline static std::map<std::string, std::string> inface_value_map = {
    {"加载目录", "cache/"},
    {"库文件名", "cvAutoTrack.dll"},
    {"项目链接", "https://download.api.weixitianli.com/cvAutoTrack.Core"},
    {"下载链接", "https://download.api.weixitianli.com/cvAutoTrack.Core/downloadUrl"},
    {"依赖链接", "https://download.api.weixitianli.com/cvAutoTrack.Core/DependFilesDownloadUrlAndHash"},
    {"库缓存文件名", "cvAutoTrack.dll"}};

inline static std::string get_value(const std::string &key)
{
    return inface_value_map[key];
}
template <typename... Args>
inline static std::string get_value(const std::string &key, Args... args)
{
    return get_value(key) + get_value(args...);
}

#endif // __INFACE_DEFINE_H__
