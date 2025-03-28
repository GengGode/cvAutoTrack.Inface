

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
    std::shared_ptr<FILE> fp_ptr(fp, [](FILE* fp) {
        if (fp)
            fclose(fp);
    });
    if (fp_ptr == nullptr)
    {
        std::cout << lib_name " not found" << std::endl;
        return 0;
    }
    return 1;
}

void show(inface& inface)
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
    int progress_callback_count = inface.get_progress_callback_count();
    std::cout << "progress_callback_count: " << progress_callback_count << std::endl;
    for (int i = 0; i < progress_callback_count; i++)
    {
        std::cout << "progress_callback[" << i << "]: " << inface.get_progress_callback_name(i) << std::endl;
    }
}

int progress(int current, int total, const char* msg)
{
    float percent = (float)current / total;
    std::cout << "progress: " << current << "/" << total << " " << percent * 100 << "%" << " " << msg << std::endl;
    return 0;
}

int main()
{
    if (!init())
        return -1;

    inface inface(lib_name);
    {
        auto str_ptr = inface.alloc_string();
        inface.get_inface_version(str_ptr);
        auto version = inface.to_string(str_ptr);
        std::cout << "inface version: " << version << std::endl;
    }

    //show(inface);

    //inface.install_progress_callback("download_progress", progress);

    //// inface.api("test download_progress", nullptr);

    //auto str_ptr = inface.alloc_string();
    //inface.get_local_core_version_list(str_ptr);
    //auto versions = inface.to_string(str_ptr);
    //std::cout << "local_version: " << versions << std::endl;

    //inface.set_string_context(str_ptr, "", 1);
    //inface.get_online_core_version_list(str_ptr);
    //versions = inface.to_string(str_ptr);
    //std::cout << "online_version: " << versions << std::endl;

    auto init_impl_res = inface.auto_init_impl();
    std::cout << "init_res: " << init_impl_res << std::endl;
    if (init_impl_res != 0)
    {
        std::cout << "init failed: " << inface.get_error_define(init_impl_res) << std::endl;
        return 0;
    }
    //auto context = inface.create_cvAutoTrack_context_v1();

    ////auto checkout_impl_res = inface.checkout_online_core("8.2.16", str_ptr);
    ////std::cout << "checkout_res: " << checkout_impl_res << std::endl;
    ////if (checkout_impl_res != 0)
    ////{
    ////    auto res = inface.to_string(str_ptr);
    ////    std::cout << "checkout failed: " << inface.get_error_define(checkout_impl_res) << res << std::endl;
    ////    return 0;
    ////}

    //inface.destroy_cvAutoTrack_context_v1(context);



    char module_buff[1024] = { 0 };
    auto module_res = inface.GetCoreModulePath(module_buff, 1024);
    if (module_res)
    {
        std::cout << "module_buff: " << module_buff << std::endl;
    }
    else
    {
        std::cout << "GetCoreModulePath failed: " << inface.get_error_define(module_res) << std::endl;
    }
    char version_buff[1024] = { 0 };
    auto version_res = inface.GetCompileVersion(version_buff, 1024);
    if (version_res)
    {
        std::cout << "version_buff: " << version_buff << std::endl;
    }
    else
    {
        std::cout << "GetCompileVersion failed: " << inface.get_error_define(version_res) << std::endl;
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
            char buff[1024] = { 0 };
            inface.GetLastErrMsg(buff, 1024);
            std::cout << "get_transform_of_map failed: " << error << " " << buff << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unknown exception" << std::endl;
    }

    auto init_res = inface.InitResource();
    std::cout << "init_res: " << init_res << std::endl;
    if (init_res != 0)
    {
        auto error = inface.GetLastErr();
        char buff[1024] = { 0 };
        inface.GetLastErrMsg(buff, 1024);
        std::cout << "init failed: " << error << " " << buff << std::endl;
        return 0;
    }

    return 0;
}