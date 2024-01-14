

#include <iostream>
#include <Windows.h>
#define explicit_link
#include <cvAutoTrack.Inface.h>

bool init()
{
    auto fp = fopen("cvAutoTrack.Inface.dll", "rb");
    std::shared_ptr<FILE> fp_ptr(fp, [](FILE *fp)
                                 { if(fp)fclose(fp); });
    if (fp_ptr == nullptr)
    {
        std::cout << "cvAutoTrack.Inface.dll not found" << std::endl;
        return 0;
    }
    return 1;
}

int main()
{
    if (!init())
        return 0;
    std::cout << "init success" << std::endl;

    inface inface;
    if (!inface.is_valid)
    {
        std::cout << "inface is invalid" << std::endl;
        return 0;
    }

    auto alloc_res = inface.alloc_string();
    if (alloc_res == nullptr)
    {
        std::cout << "alloc_res is nullptr" << std::endl;
        return 0;
    }
    int error_define_count = inface.get_error_define_count();
    std::cout << "error_define_count: " << error_define_count << std::endl;
    for (int i = 0; i < error_define_count; i++)
    {
        std::cout << "error_define[" << i << "]: " << inface.get_error_define(i) << std::endl;
    }

    auto init_res = inface.auto_init_impl();
    std::cout << "init_res: " << init_res << std::endl;
    if (init_res != 0)
    {
        std::cout << "init failed: " << inface.get_error_define(init_res) << std::endl;
        return 0;
    }
    double x, y, a;
    int mapId;
    auto get_transform_of_map_res = inface.GetTransformOfMap(x, y, a, mapId);
    std::cout << "get_transform_of_map_res: " << get_transform_of_map_res << std::endl;

    return 0;
}