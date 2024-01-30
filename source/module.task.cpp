#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

int get_task_callback_count()
{
    return inface_task_map.size();
}

int get_task_callback_name(int index, inface_string_ptr result)
{
    if (index < 0 || index >= inface_task_map.size())
        return error("error index out of range");
    auto iter = inface_task_map.begin();
    for (int i = 0; i < index; i++)
        iter++;
    result->context = iter->first;
    return 0;
}

int install_task_callback(const char *task_name, int (*callback)(const char * /*json*/))
{
    if (task_name == nullptr)
        return error("task_name is null");

    inface_task_map[task_name] = [callback](std::string json) -> int
    {
        return callback(json.c_str());
    };
    return 0;
}

int remove_task_callback(const char *task_name)
{
    if (task_name == nullptr)
        return error("task_name is null");

    inface_task_map[task_name] = nullptr;
    return 0;
}