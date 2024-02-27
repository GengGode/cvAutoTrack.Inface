#include "cvAutoTrack.Inface.h"
#include "Inface.define.h"
#include "Inface.regerr.h"

#include <iostream>
#include <thread>
bool api(const char* json, inface_string_ptr result)
{
    if(json == nullptr)
        return error("json是空指针");

    std::string json_str = json;
    if(json_str == "test download_progress")
    {
        auto fun =  inface::progress_map["download_progress"];
        if(fun)
        {
            for(int i = 0; i < 100; i++)
            {
                fun(i, 100, "test download_progress");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        else
        {
            return error("progress_name不存在");
        }

    }
    return 0;
    
}
