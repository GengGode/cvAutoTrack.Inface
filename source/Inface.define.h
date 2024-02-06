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
    {"cvAutoTrack dll path", "cache/"},
    {"cvAutoTrack dll name", "cvAutoTrack.dll"},
    {"cvAutoTrack url", "https://download.api.weixitianli.com/cvAutoTrack.Core"},
    {"cvAutoTrack download url path", "https://download.api.weixitianli.com/cvAutoTrack.Core/downloadUrl"},
    {"cvAutoTrack deps download url path", "https://download.api.weixitianli.com/cvAutoTrack.Core/DependFilesDownloadUrlAndHash"},
    {"cvAutoTrack download cache name", "cvAutoTrack.dll"}};

#endif // __INFACE_DEFINE_H__
