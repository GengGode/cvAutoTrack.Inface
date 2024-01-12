#ifndef CVAUTOTRACE_INFACE_H
#define CVAUTOTRACE_INFACE_H

#ifdef CVAUTOTRACE_INFACE_EXPORTS
#define CVAUTOTRACE_INFACE_API __declspec(dllexport)
#else
#define CVAUTOTRACE_INFACE_API __declspec(dllimport)
#endif

#if __cplusplus
extern "C" {
#endif

// string alloc
struct inface_string;
typedef struct inface_string* inface_string_ptr;

// check cvAutoTrace.dll is valid
CVAUTOTRACE_INFACE_API bool check_impl_valid();
// get cvAutoTrace.dll version
CVAUTOTRACE_INFACE_API int auto_init_impl();
// set callback
CVAUTOTRACE_INFACE_API void set_callback(void* callback);

// string alloc and free
CVAUTOTRACE_INFACE_API inface_string_ptr alloc_string();
CVAUTOTRACE_INFACE_API void free_string(inface_string_ptr str);

// proxy for cvAutoTrace.dll
CVAUTOTRACE_INFACE_API bool api(const char* json, char* result, int size);
CVAUTOTRACE_INFACE_API bool api_alloc(const char* json, inface_string_ptr result);

#if __cplusplus
}
#endif

#endif // CVAUTOTRACE_INFACE_H
