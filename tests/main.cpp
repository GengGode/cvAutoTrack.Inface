

#include <iostream>
#include <Windows.h>

struct inface_string;
typedef struct inface_string *inface_string_ptr;

typedef inface_string_ptr (*alloc_string_t)();
typedef int (*get_string_length_t)(inface_string_ptr str);
typedef int (*get_string_context_t)(inface_string_ptr str, char *buffer, int buffer_size);
typedef void (*free_string_t)(inface_string_ptr str);
typedef int (*get_last_error_t)();
typedef int (*get_error_define_count_t)();
typedef int (*get_error_define_t)(int index, inface_string_ptr result);
typedef bool (*check_impl_valid_t)();
typedef int (*auto_init_impl_t)();

struct inface
{
    HMODULE lib;
    bool is_valid = false;

    alloc_string_t alloc_string_func;
    get_string_length_t get_string_length_func;
    get_string_context_t get_string_context_func;
    free_string_t free_string_func;
    get_last_error_t get_last_error_func;
    get_error_define_count_t get_error_define_count_func;
    get_error_define_t get_error_define_func;
    check_impl_valid_t check_impl_valid_func;
    auto_init_impl_t auto_init_impl_func;

    inface()
    {
        lib = LoadLibrary("cvAutoTrack.Inface.dll");
        if (lib == nullptr)
            return;
        is_valid = true;

        alloc_string_func = (alloc_string_t)GetProcAddress(lib, "alloc_string");
        get_string_length_func = (get_string_length_t)GetProcAddress(lib, "get_string_length");
        get_string_context_func = (get_string_context_t)GetProcAddress(lib, "get_string_context");
        free_string_func = (free_string_t)GetProcAddress(lib, "free_string");
        get_last_error_func = (get_last_error_t)GetProcAddress(lib, "get_last_error");
        get_error_define_count_func = (get_error_define_count_t)GetProcAddress(lib, "get_error_define_count");
        get_error_define_func = (get_error_define_t)GetProcAddress(lib, "get_error_define");
        check_impl_valid_func = (check_impl_valid_t)GetProcAddress(lib, "check_impl_valid");
        auto_init_impl_func = (auto_init_impl_t)GetProcAddress(lib, "auto_init_impl");
    }
    ~inface()
    {
        if (lib != nullptr)
            FreeLibrary(lib);
    }

    inface_string_ptr alloc_string()
    {
        if (alloc_string_func == nullptr)
            return nullptr;
        return alloc_string_func();
    }
    int get_string_length(inface_string_ptr str)
    {
        if (get_string_length_func == nullptr)
            return 0;
        return get_string_length_func(str);
    }
    int get_string_context(inface_string_ptr str, char *buffer, int buffer_size)
    {
        if (get_string_context_func == nullptr)
            return 0;
        return get_string_context_func(str, buffer, buffer_size);
    }
    void free_string(inface_string_ptr str)
    {
        if (free_string_func == nullptr)
            return;
        free_string_func(str);
    }
    int get_last_error()
    {
        if (get_last_error_func == nullptr)
            return 0;
        return get_last_error_func();
    }
    int get_error_define_count()
    {
        if (get_error_define_count_func == nullptr)
            return 0;
        return get_error_define_count_func();
    }
    int get_error_define(int index, inface_string_ptr result)
    {
        if (get_error_define_func == nullptr)
            return 0;
        return get_error_define_func(index, result);
    }
    bool check_impl_valid()
    {
        if (check_impl_valid_func == nullptr)
            return false;
        return check_impl_valid_func();
    }
    int auto_init_impl()
    {
        if (auto_init_impl_func == nullptr)
            return 0;
        return auto_init_impl_func();
    }

    std::string get_error_define(int index)
    {
        auto alloc_res = alloc_string();
        auto get_error_define_res = get_error_define(index, alloc_res);
        auto get_string_length_res = get_string_length(alloc_res);
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        auto get_string_context_res = get_string_context(alloc_res, buffer, sizeof(buffer));
        std::string result = buffer;
        free_string(alloc_res);
        return result;
    }
};

bool init()
{

    std::shared_ptr<FILE> fp_ptr(fopen("cvAutoTrack.Inface.dll", "rb"), [](FILE *fp)
                                 { fclose(fp); });
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

    return 0;
}