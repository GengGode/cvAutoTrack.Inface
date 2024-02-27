#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

int get_progress_callback_count()
{
    return inface::progress_map.size();
}

int get_progress_callback_name(int index, inface_string_ptr result)
{
    if (index < 0 || index >= inface::progress_map.size())
        return error("回调表的索引超出范围");
    auto iter = inface::progress_map.begin();
    for (int i = 0; i < index; i++)
        iter++;
    result->context = iter->first;
    return 0;
}

int install_progress_callback(const char *progress_name, int (*callback)(int /*current*/, int /*total*/, const char* /*msg*/))
{
    if (progress_name == nullptr)
        return error("progress_name是空指针");

    inface::progress_map[progress_name] = [callback](int current, int total, std::string msg) -> int
    {
        return callback(current, total, msg.c_str());
    };
    return 0;
}

int remove_progress_callback(const char *progress_name)
{
    if (progress_name == nullptr)
        return error("progress_name是空指针");

    inface::progress_map[progress_name] = nullptr;
    return 0;
}