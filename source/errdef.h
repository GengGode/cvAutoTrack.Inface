#include <cstdio>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <source_location>
#include <optional>

template <size_t n>
struct SourceLocation
{
    constexpr SourceLocation(const char (&_path)[n], size_t _lineno, size_t _colno)
    {
        std::copy_n(_path, n, path);
        lineno = _lineno;
        colno = _colno;
    }

    char path[n];
    size_t lineno;
    size_t colno;
};

template <size_t n>
struct ErrorMessage
{
    constexpr ErrorMessage(const char (&_msg)[n])
    {
        std::copy_n(_msg, n, msg);
    }

    char msg[n];
};

class ErrorInvoker
{
public:
    struct location
    {
        std::string m_path;
        size_t m_lineno;
        size_t m_colno;
        std::string m_errmsg;
    };
    inline static std::vector<location> m_locations = {{"default", 0, 0, "success"}};
    ErrorInvoker(const std::string &path, size_t lineno, size_t colno, const std::string &errmsg)
    {
        m_locations.push_back(location{path, lineno, colno, errmsg});
    }
};

template <typename Fucker, SourceLocation srclocation, ErrorMessage msg>
class BadFucker
{
public:
    inline static Fucker fu = {srclocation.path, srclocation.lineno, srclocation.colno, msg.msg};
    template <typename Ft, typename... ArgTs>
    static auto callback(Ft f, ArgTs... args)
    {
        return f(args...);
    }
};

int error_impl(const char *sz)
{
    int index = 0;
    for (auto &[_, __, ___, errmsg] : ErrorInvoker::m_locations)
    {
        if (errmsg == sz)
            break;
        index++;
    }
    return index;
}

#define error(msg) BadFucker<ErrorInvoker, SourceLocation(__FILE__, std::source_location::current().line(), std::source_location::current().column()), ErrorMessage(msg)>::callback(error_impl, msg)

std::set<std::string> get_all_error_info()
{
    std::set<std::string> all_error_info;
    for (auto &[_, __, ___, errmsg] : ErrorInvoker::m_locations)
    {
        all_error_info.insert(errmsg);
    }
    return all_error_info;
}
