#include "cvAutoTrack.Inface.h"
#include "string.match.h"
#include "Inface.regerr.h"
#include "Inface.define.h"
#include "Inface.library.h"
#include "Inface.network.h"
#include "Inface.powershell.h"
#include <filesystem>

int get_local_core_version_list(inface_string_ptr result)
{
    std::string version_list;
    {
        std::filesystem::path path = get_value("下载目录");
        if (path.empty())
            return error("下载目录为空");
        if (!std::filesystem::exists(path))
            return error("下载目录不存在");
        if (!std::filesystem::is_directory(path))
            return error("下载目录不是目录");
        for (auto &p : std::filesystem::directory_iterator(path))
        {
            if (p.is_regular_file())
            {
                auto file = p.path();
                if (match(file.filename().string(), "cvAutoTrack-\\d+\\.\\d+\\.\\d+\\.zip"))
                    version_list += file.filename().string() + "\n";
            }
        }
    }
    if (version_list.empty())
    {
        return error("下载目录中没有版本");
    }
    int err = set_string_context(result, version_list.c_str(), version_list.size());
    if (err != 0)
        return error("设置本地版本列表失败");
    return 0;
}