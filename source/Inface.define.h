#ifndef __INFACE_DEFINE_H__
#define __INFACE_DEFINE_H__
#include <string>

// string alloc
struct inface_string
{
    std::string context;
};
typedef struct inface_string *inface_string_ptr;

#endif // __INFACE_DEFINE_H__
