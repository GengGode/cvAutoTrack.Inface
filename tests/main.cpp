

#include <iostream>

#define explicit_link
#include <cvAutoTrack.Inface.h>

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#define lib_name "cvAutoTrack.Inface.dll"
#else
#define lib_name "libcvAutoTrack.Inface.so"
#endif
bool init()
{
    auto fp = fopen(lib_name, "rb");
    std::shared_ptr<FILE> fp_ptr(fp, [](FILE *fp)
                                 { if(fp)fclose(fp); });
    if (fp_ptr == nullptr)
    {
        std::cout << lib_name " not found" << std::endl;
        return 0;
    }
    return 1;
}

void show(inface &inface)
{
    int error_define_count = inface.get_error_define_count();
    std::cout << "error_define_count: " << error_define_count << std::endl;
    for (int i = 0; i < error_define_count; i++)
    {
        std::cout << "error_define[" << i << "]: " << inface.get_error_define(i) << std::endl;
    }
    int task_callback_count = inface.get_task_callback_count();
    std::cout << "task_callback_count: " << task_callback_count << std::endl;
    for (int i = 0; i < task_callback_count; i++)
    {
        std::cout << "task_callback[" << i << "]: " << inface.get_task_callback_name(i) << std::endl;
    }
}

int main()
{
    if (!init())
        return 0;
    std::cout << "init success" << std::endl;

    inface inface(lib_name);
    if (!inface.is_valid)
    {
        std::cout << "inface is invalid" << std::endl;
        return 0;
    }

    auto init_impl_res = inface.auto_init_impl();
    std::cout << "init_res: " << init_impl_res << std::endl;
    if (init_impl_res != 0)
    {
        std::cout << "init failed: " << inface.get_error_define(init_impl_res) << std::endl;
        return 0;
    }
    char module_buff[1024] = {0};
    auto module_res = inface.GetCoreModulePath(module_buff, 1024);
    if (module_res)
    {
        std::cout << "module_buff: " << module_buff << std::endl;
    }
    else
    {
        std::cout << "GetCoreModulePath failed: " << inface.get_error_define(module_res) << std::endl;
    }

    try
    {
        double x, y, a;
        int mapId;
        auto get_transform_of_map_res = inface.GetTransformOfMap(x, y, a, mapId);
        std::cout << "get_transform_of_map_res: " << get_transform_of_map_res << std::endl;
        if (get_transform_of_map_res == 0)
        {
            auto error = inface.GetLastErr();
            char buff[1024] = {0};
            inface.GetLastErrMsg(buff, 1024);
            std::cout << "get_transform_of_map failed: " << error << " " << buff << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unknown exception" << std::endl;
    }

    auto init_res = inface.init();
    std::cout << "init_res: " << init_res << std::endl;
    if (init_res != 0)
    {
        auto error = inface.GetLastErr();
        char buff[1024] = {0};
        inface.GetLastErrMsg(buff, 1024);
        std::cout << "init failed: " << error << " " << buff << std::endl;
        return 0;
    }

    return 0;
}