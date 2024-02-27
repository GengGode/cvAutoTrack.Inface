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

// task progress value
class inface{
public:
inline static std::map<std::string, std::function<int(std::string)>> task_map = {
    {"download_start", nullptr},
    {"download_progress", nullptr},
    {"download_failed", nullptr},
    {"download_success", nullptr}};
inline static std::map<std::string, std::function<int(int,int,std::string)>> progress_map = {
    {"download_progress", nullptr}};
inline static std::map<std::string, std::string> value_map = {
    {"下载目录", "cache/"},
    {"加载目录", "core/"},
    {"依赖目录", "core/deps/"},
    {"资源目录", "core/deps/"},
    {"库文件名", "cvAutoTrack.dll"},
    {"项目链接", "https://download.api.weixitianli.com/cvAutoTrack.Core"},
    {"依赖链接", "https://download.api.weixitianli.com/cvAutoTrack.Core/DependFilesDownloadUrlAndHash"},
    {"强制使用本地版本", "false"}};
};

inline static std::string get_value(const std::string &key)
{
    return inface::value_map[key];
}
template <typename... Args>
inline static std::string get_value(const std::string &key, Args... args)
{
    return get_value(key) + get_value(args...);
}

#endif // __INFACE_DEFINE_H__
