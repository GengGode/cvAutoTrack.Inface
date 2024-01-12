#include "cvAutoTrace.Inface.h"
#include "Inface.define.h"

// check cvAutoTrace.dll is valid
bool check_impl_valid()
{
    return true;
}
// get cvAutoTrace.dll version
int auto_init_impl()
{
    return 0;
}
// set callback
void set_callback(void *callback)
{
}

// proxy for cvAutoTrace.dll
bool api(const char *json, char *result, int size)
{
    return false;
}
bool api_alloc(const char *json, inface_string_ptr result)
{
    return false;
}
