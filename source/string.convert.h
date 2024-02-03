#ifndef __STRING_CONVERT_H__
#define __STRING_CONVERT_H__
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
#include <Windows.h>
#else
#include <iconv.h>
#include <cstring>
#endif
#include <string>
namespace utils
{
    static std::string utf8_to_gbk(const std::string &utf8_string)
    {
        std::string ret_string;
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, NULL, 0);
        wchar_t *gbk_wstring = new wchar_t[len + 1];
        memset(gbk_wstring, 0, len * 2 + 2);
        MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, gbk_wstring, len);
        len = WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, NULL, 0, NULL, NULL);
        char *gbk_string = new char[len + 1];
        memset(gbk_string, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, gbk_string, len, NULL, NULL);
        ret_string = gbk_string;
        delete[] gbk_string;
        delete[] gbk_wstring;
#else
        iconv_t cd = iconv_open("GBK", "UTF-8");
        if (cd == (iconv_t)-1)
            return ret_string;
        size_t in_size = utf8_string.size();
        size_t out_size = in_size * 2;
        char *in_buf = new char[in_size + 1];
        char *out_buf = new char[out_size + 1];
        memset(in_buf, 0, in_size + 1);
        memset(out_buf, 0, out_size + 1);
        memcpy(in_buf, utf8_string.c_str(), in_size);
        char *in_ptr = in_buf;
        char *out_ptr = out_buf;
        size_t ret = iconv(cd, &in_ptr, &in_size, &out_ptr, &out_size);
        if (ret == (size_t)-1)
        {
            delete[] in_buf;
            delete[] out_buf;
            iconv_close(cd);
            return ret_string;
        }
        ret_string = out_buf;
        delete[] in_buf;
        delete[] out_buf;
        iconv_close(cd);
#endif
        return ret_string;
    }

    static std::string gbk_to_utf8(const std::string &gbk_string)
    {
        std::string ret_string;
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
        int len = MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, NULL, 0);
        wchar_t *utf8_wstring = new wchar_t[len + 1];
        memset(utf8_wstring, 0, len * 2 + 2);
        MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, utf8_wstring, len);
        len = WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, NULL, 0, NULL, NULL);
        char *utf8_string = new char[len + 1];
        memset(utf8_string, 0, len + 1);
        WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, utf8_string, len, NULL, NULL);
        ret_string = utf8_string;
        delete[] utf8_string;
        delete[] utf8_wstring;
#else
        iconv_t cd = iconv_open("UTF-8", "GBK");
        if (cd == (iconv_t)-1)
            return ret_string;
        size_t in_size = gbk_string.size();
        size_t out_size = in_size * 2;
        char *in_buf = new char[in_size + 1];
        char *out_buf = new char[out_size + 1];
        memset(in_buf, 0, in_size + 1);
        memset(out_buf, 0, out_size + 1);
        memcpy(in_buf, gbk_string.c_str(), in_size);
        char *in_ptr = in_buf;
        char *out_ptr = out_buf;
        size_t ret = iconv(cd, &in_ptr, &in_size, &out_ptr, &out_size);
        if (ret == (size_t)-1)
        {
            delete[] in_buf;
            delete[] out_buf;
            iconv_close(cd);
            return ret_string;
        }
        ret_string = out_buf;
        delete[] in_buf;
        delete[] out_buf;
        iconv_close(cd);
#endif
        return ret_string;
    }

    static std::string to_string(const std::wstring &wstring)
    {
        std::string ret_string;
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
        int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), -1, NULL, 0, NULL, NULL);
        char *utf8_string = new char[len + 1];
        memset(utf8_string, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), -1, utf8_string, len, NULL, NULL);
        ret_string = utf8_string;
        delete[] utf8_string;
#else
        iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
        if (cd == (iconv_t)-1)
            return ret_string;
        size_t in_size = wstring.size() * 2;
        size_t out_size = in_size * 2;
        char *in_buf = new char[in_size + 1];
        char *out_buf = new char[out_size + 1];
        memset(in_buf, 0, in_size + 1);
        memset(out_buf, 0, out_size + 1);
        memcpy(in_buf, wstring.c_str(), in_size);
        char *in_ptr = in_buf;
        char *out_ptr = out_buf;
        size_t ret = iconv(cd, &in_ptr, &in_size, &out_ptr, &out_size);
        if (ret == (size_t)-1)
        {
            delete[] in_buf;
            delete[] out_buf;
            iconv_close(cd);
            return ret_string;
        }
        ret_string = out_buf;
        delete[] in_buf;
        delete[] out_buf;
        iconv_close(cd);
#endif
        return ret_string;
    }

    static std::wstring to_wstring(const std::string &string)
    {
        std::wstring ret_string;
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN128) || defined(__CYGWIN__)
        int len = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, NULL, 0);
        wchar_t *utf8_wstring = new wchar_t[len + 1];
        memset(utf8_wstring, 0, len * 2 + 2);
        MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, utf8_wstring, len);
        ret_string = utf8_wstring;
        delete[] utf8_wstring;
#else
        iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
        if (cd == (iconv_t)-1)
            return ret_string;
        size_t in_size = string.size();
        size_t out_size = in_size * 2;
        char *in_buf = new char[in_size + 1];
        char *out_buf = new char[out_size + 1];
        memset(in_buf, 0, in_size + 1);
        memset(out_buf, 0, out_size + 1);
        memcpy(in_buf, string.c_str(), in_size);
        char *in_ptr = in_buf;
        char *out_ptr = out_buf;
        size_t ret = iconv(cd, &in_ptr, &in_size, &out_ptr, &out_size);
        if (ret == (size_t)-1)
        {
            delete[] in_buf;
            delete[] out_buf;
            iconv_close(cd);
            return ret_string;
        }
        ret_string = std::wstring(out_buf, out_buf + out_size);
        delete[] in_buf;
        delete[] out_buf;
        iconv_close(cd);
#endif
        return ret_string;
    }

    static bool is_utf8(const std::string &string)
    {
        auto gbk_string = utf8_to_gbk(string);
        auto utf8_string = gbk_to_utf8(gbk_string);
        return utf8_string == string;
    }

    static std::string to_utf8(const std::string &string)
    {
        if (is_utf8(string))
            return string;
        else
            return gbk_to_utf8(string);
    }

    static std::string to_gbk(const std::string &string)
    {
        if (is_utf8(string))
            return utf8_to_gbk(string);
        else
            return string;
    }
} // namespace utils

#endif // __STRING_CONVERT_H__