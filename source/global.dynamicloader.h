#ifndef __GLOBAL_DYNAMICLOADER_H__
#define __GLOBAL_DYNAMICLOADER_H__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
    #include <windows.h>
    #define library_handle_t HMODULE
    #define set_dll_path(path) SetDllDirectory(path.c_str())
    #define load_lib(path) LoadLibrary(path.c_str())
    #define free_lib(lib) FreeLibrary(lib)
    #define get_proc(lib, name) GetProcAddress(lib, name)
#else
    #include <dlfcn.h>
    #include <unistd.h>
    #define library_handle_t void*
    #define set_dll_path(path)
    #define load_lib(path) dlopen(path.c_str(), RTLD_LAZY)
    #define free_lib(lib) dlclose(lib)
    #define get_proc(lib, name) dlsym(lib, name)
#endif

#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

template <auto Api>
//    requires(std::is_pointer_v<decltype(Api)> && std::is_function_v<std::remove_pointer_t<decltype(Api)>>)
struct function_traits
{
    static constexpr auto name = []() constexpr {
#if defined(_MSC_VER)
        auto s = []() constexpr {
            constexpr std::string_view s = __FUNCSIG__;
            constexpr std::string_view begin_key = "function_traits<";
            constexpr std::string_view end_key = "::operator ()(void) const";
            auto pos = s.find(begin_key) + begin_key.size();
            auto end = s.find(end_key);
            if (pos == std::string_view::npos || end == std::string_view::npos)
                return std::string_view{};
            auto sub = s.substr(pos, end - pos);
            end = sub.rfind(">::");
            return sub.substr(0, end);
        }();

        constexpr std::string_view key = "__cdecl ";
        auto pos = s.find(key) + key.size();
        if (pos == std::string_view::npos)
            return std::string_view{};
        auto sub = s.substr(pos);
        auto end = sub.find("(");
        if (end == std::string_view::npos)
            return std::string_view{};
        sub = sub.substr(0, end);
        return sub;
#else
        return std::string_view{};
#endif
    }();
    using type = decltype(Api);
};

template <auto... Apis> class dynamic_loader
{
public:
    dynamic_loader() : handle(nullptr) {}
    dynamic_loader(const std::string& library_path) : handle(nullptr) { load(library_path); }
    ~dynamic_loader() { unload(); }
    dynamic_loader(const dynamic_loader&) = delete;
    dynamic_loader& operator=(const dynamic_loader&) = delete;
    dynamic_loader(dynamic_loader&& other) noexcept : handle(other.handle), func_ptrs(std::move(other.func_ptrs)) { other.handle = nullptr; }
    dynamic_loader& operator=(dynamic_loader&& other) noexcept
    {
        if (this != &other)
        {
            if (handle && handle != nullptr)
                free_library(handle);
            handle = other.handle;
            func_ptrs = std::move(other.func_ptrs);
            other.handle = nullptr;
        }
        return *this;
    }

    bool load(const std::string& library_path)
    {
        if (handle = load_lib(library_path.c_str()); !handle)
            return false;
        return load_all(), true;
    }
    void unload()
    {
        if (handle)
        {
            free_lib(handle);
            handle = nullptr;
        }
    }
    bool is_loaded() const { return handle; }

    template <auto Api> auto get() -> typename function_traits<Api>::type { return std::get<typename function_traits<Api>::type>(func_ptrs); }
    template <auto Api, typename... Args> auto call(Args&&... args) -> decltype(auto)
    {
        auto func = get<Api>();
        if (!func)
            throw std::runtime_error("Function pointer is null");
        return func(std::forward<Args>(args)...);
    }

private:
    library_handle_t handle;
    std::tuple<typename function_traits<Apis>::type...> func_ptrs;

private:
    template <auto Api> void load_function()
    {
        auto& ptr = std::get<typename function_traits<Api>::type>(func_ptrs);
        auto symbol = std::string(function_traits<Api>::name);
        ptr = reinterpret_cast<typename function_traits<Api>::type>(get_proc(handle, symbol.c_str()));

        if (!ptr)
            throw std::runtime_error(std::string("Failed to load function: ") + symbol);
    }
    void load_all() { (load_function<Apis>(), ...); }
};

#endif // __GLOBAL_DYNAMICLOADER_H__