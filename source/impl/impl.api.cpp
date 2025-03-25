#include <cvAutoTrack.Inface.h>
#include "Inface.library.h"

#define maroc_concatenate(a, b) maroc_concatenate_1(a, b)
#define maroc_concatenate_1(a, b) maroc_concatenate_2(a, b)
#define maroc_concatenate_2(a, b) a##b
#define maroc_expand(x) x
#define maroc_for_each_0(pred, ...)
#define maroc_for_each_1(pred, n, x, ...) pred(x, 0)
#define maroc_for_each_2(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_1(pred, 1, __VA_ARGS__))
#define maroc_for_each_3(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_2(pred, 2, __VA_ARGS__))
#define maroc_for_each_4(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_3(pred, 3, __VA_ARGS__))
#define maroc_for_each_5(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_4(pred, 4, __VA_ARGS__))
#define maroc_for_each_6(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_5(pred, 5, __VA_ARGS__))
#define maroc_for_each_7(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_6(pred, 6, __VA_ARGS__))
#define maroc_for_each_8(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_7(pred, 7, __VA_ARGS__))
#define maroc_for_each_9(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_8(pred, 8, __VA_ARGS__))
#define maroc_for_each_10(pred, n, x, ...) pred(x, n) maroc_expand(maroc_for_each_9(pred, 9, __VA_ARGS__))
#define maroc_args_count(...) maroc_expand(maroc_arg_count_1(0, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define maroc_arg_count_1(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, n, ...) n
#define maroc_for_each_(n, pred, ...) maroc_expand(maroc_concatenate(maroc_for_each_, n)(pred, n, __VA_ARGS__))
#define maroc_for_each(pred, ...) maroc_expand(maroc_for_each_(maroc_expand(maroc_args_count(__VA_ARGS__)), pred, __VA_ARGS__))
#define comma_0()
#define comma_1() ,
#define comma_2() ,
#define comma_3() ,
#define comma_4() ,
#define comma_5() ,
#define comma_6() ,
#define comma_7() ,
#define comma_8() ,
#define comma_9() ,

typedef long long int long_long_int;
typedef const char *const_char_ptr;
typedef char *char_ptr;
typedef bool &bool_ref;
typedef int &int_ref;
typedef double &double_ref;
#define type_null_
#define type_null_bool
#define type_null_int
#define type_null_double
#define type_null_bool_ref
#define type_null_int_ref
#define type_null_double_ref
#define type_null_long_long_int
#define type_null_const_char_ptr
#define type_null_char_ptr

#define type_null_cvatv1_ptr

#define ret_cvatv1_ptr_false nullptr
typedef cvAutoTrackContextV1Ptr cvatv1_ptr;
#define only_name(v, n) \
    type_null_##v comma_##n()
#define bind_call(name, ...)                                               \
    name(__VA_ARGS__)                                                      \
    {                                                                      \
        auto func = (decltype(&name))get_proc(get_global_handle(), #name); \
        if (func == nullptr)                                               \
            return false;                                                  \
        return func(maroc_for_each(only_name, __VA_ARGS__));               \
    }
#define ret_bind_call(ret_type, name, ...)                                 \
    ret_type name(__VA_ARGS__)                                             \
    {                                                                      \
        auto func = (decltype(&name))get_proc(get_global_handle(), #name); \
        if (func == nullptr)                                               \
            return ret_##ret_type##_false;                                 \
        return func(maroc_for_each(only_name, __VA_ARGS__));               \
    }
#define void_bind_call(name, ...)                                          \
    void name(__VA_ARGS__)                                                 \
    {                                                                      \
        auto func = (decltype(&name))get_proc(get_global_handle(), #name); \
        if (func == nullptr)                                               \
            return;                                                        \
        return func(maroc_for_each(only_name, __VA_ARGS__));               \
    }

ret_bind_call(cvatv1_ptr, create_cvAutoTrack_context_v1);
void_bind_call(destroy_cvAutoTrack_context_v1, cvatv1_ptr context);
bool bind_call(init);
bool bind_call(uninit);
bool bind_call(startServe);
bool bind_call(stopServe);
bool bind_call(SetUseBitbltCaptureMode);
bool bind_call(SetUseDx11CaptureMode);
bool bind_call(SetHandle, long_long_int handle);
bool bind_call(SetWorldCenter, double x, double y);
bool bind_call(SetWorldScale, double scale);
bool bind_call(ImportMapBlock, int id_x, int id_y, const_char_ptr image_data, int image_data_size, int image_width, int image_height);
bool bind_call(ImportMapBlockCenter, int x, int y);
bool bind_call(ImportMapBlockCenterScale, int x, int y, double scale);
bool bind_call(GetTransformOfMap, double_ref x, double_ref y, double_ref a, int_ref mapId);
bool bind_call(GetPositionOfMap, double_ref x, double_ref y, int_ref mapId);
bool bind_call(GetDirection, double_ref a);
bool bind_call(GetRotation, double_ref a);
bool bind_call(GetStar, double_ref x, double_ref y, bool_ref isEnd);
bool bind_call(GetStarJson, char_ptr jsonBuff);
bool bind_call(GetUID, int_ref uid);
bool bind_call(GetAllInfo, double_ref x, double_ref y, int_ref mapId, double_ref a, double_ref r, int_ref uid);
bool bind_call(GetInfoLoadPicture, char_ptr path, int_ref uid, double_ref x, double_ref y, double_ref a);
bool bind_call(GetInfoLoadVideo, char_ptr path, char_ptr pathOutFile);
bool bind_call(DebugCapture);
bool bind_call(DebugCapturePath, const_char_ptr path_buff, int buff_size);
int bind_call(GetLastErr);
int bind_call(GetLastErrMsg, char_ptr msg_buff, int buff_size);
int bind_call(GetLastErrJson, char_ptr json_buff, int buff_size);
bool bind_call(SetDisableFileLog);
bool bind_call(SetEnableFileLog);
bool bind_call(GetCompileVersion, char_ptr version_buff, int buff_size);
bool bind_call(GetCompileTime, char_ptr time_buff, int buff_size);
bool bind_call(GetCoreModulePath, char_ptr path_buff, int buff_size);