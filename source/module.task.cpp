#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

int get_task_callback_count()
{
    return inface::task_map.size();
}

int get_task_callback_name(int index, inface_string_ptr result)
{
    if (index < 0 || index >= inface::task_map.size())
        return error("回调表的索引超出范围");
    auto iter = inface::task_map.begin();
    for (int i = 0; i < index; i++)
        iter++;
    result->context = iter->first;
    return 0;
}

int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/))
{
    if (task_name == nullptr)
        return error("task_name是空指针");

    inface::task_map[task_name] = [callback](std::string json) -> int
    {
        return callback(json.c_str());
    };
    return 0;
}

int remove_task_callback(const char *task_name)
{
    if (task_name == nullptr)
        return error("task_name是空指针");

    inface::task_map[task_name] = nullptr;
    return 0;
}