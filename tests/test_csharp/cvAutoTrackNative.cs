using Windows.Win32.Foundation.Metadata;
namespace cvAutoTrackNative
{
    public unsafe partial struct cvAutoTrackContextV1
    {
        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> DebugLoadMapImagePath;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> InitResource;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> UnInitResource;

        [NativeTypeName("bool (*)(const char *, const char *, const char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, sbyte*, sbyte*, int, byte> SetCacheConfig;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> SetCoreCachePath;

        [NativeTypeName("bool (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, byte> GetCoreCachePath;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> StartServer;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> StopServer;

        [NativeTypeName("bool (*)(int)")]
        public delegate* unmanaged[Cdecl]<int, byte> SetServerInterval;

        [NativeTypeName("bool (*)(void (*)(const char *, int))")]
        public delegate* unmanaged[Cdecl]<delegate* unmanaged[Cdecl]<sbyte*, int, void>, byte> SetServerCallback;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetDisableFileLog;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetEnableFileLog;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> SetLogFilePath;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> SetLogFileName;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetUseBitbltCaptureMode;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetUseGraphicsCaptureMode;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetUseDwmCaptureMode;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetUseLocalPictureMode;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> SetUseLocalVideoMode;

        [NativeTypeName("bool (*)(long long)")]
        public delegate* unmanaged[Cdecl]<long, byte> SetCaptureHandle;

        [NativeTypeName("bool (*)(long long (*)())")]
        public delegate* unmanaged[Cdecl]<delegate* unmanaged[Cdecl]<long>, byte> SetCaptureHandleCallback;

        [NativeTypeName("bool (*)(void (*)(const char *, int &))")]
        public delegate* unmanaged[Cdecl]<delegate* unmanaged[Cdecl]<sbyte*, int*, void>, byte> SetScreenSourceCallback;

        [NativeTypeName("bool (*)(void (*)(const char *, int &, int &, int &))")]
        public delegate* unmanaged[Cdecl]<delegate* unmanaged[Cdecl]<sbyte*, int*, int*, int*, void>, byte> SetScreenSourceCallbackEx;

        [NativeTypeName("bool (*)(const char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, byte> SetScreenSourceImage;

        [NativeTypeName("bool (*)(const char *, int, int, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, int, int, byte> SetScreenSourceImageEx;

        [NativeTypeName("bool (*)(void (*)(int &, int &, int &, int &))")]
        public delegate* unmanaged[Cdecl]<delegate* unmanaged[Cdecl]<int*, int*, int*, int*, void>, byte> SetScreenClientRectCallback;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> SetTrackCachePath;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> SetTrackCacheName;

        [NativeTypeName("bool (*)(double, double)")]
        public delegate* unmanaged[Cdecl]<double, double, byte> SetWorldCenter;

        [NativeTypeName("bool (*)(double)")]
        public delegate* unmanaged[Cdecl]<double, byte> SetWorldScale;

        [NativeTypeName("bool (*)(double &, double &, double &, int &)")]
        public delegate* unmanaged[Cdecl]<double*, double*, double*, int*, byte> GetTransformOfMap;

        [NativeTypeName("bool (*)(double &, double &, int &)")]
        public delegate* unmanaged[Cdecl]<double*, double*, int*, byte> GetPositionOfMap;

        [NativeTypeName("bool (*)(double &)")]
        public delegate* unmanaged[Cdecl]<double*, byte> GetDirection;

        [NativeTypeName("bool (*)(double &)")]
        public delegate* unmanaged[Cdecl]<double*, byte> GetRotation;

        [NativeTypeName("bool (*)(int &)")]
        public delegate* unmanaged[Cdecl]<int*, byte> GetUID;

        [NativeTypeName("bool (*)(double &, double &, int &, double &, double &, int &)")]
        public delegate* unmanaged[Cdecl]<double*, double*, int*, double*, double*, int*, byte> GetAllInfo;

        [NativeTypeName("bool (*)()")]
        public delegate* unmanaged[Cdecl]<byte> DebugCapture;

        [NativeTypeName("bool (*)(const char *)")]
        public delegate* unmanaged[Cdecl]<sbyte*, byte> DebugCapturePath;

        [NativeTypeName("int (*)()")]
        public delegate* unmanaged[Cdecl]<int> GetLastErr;

        [NativeTypeName("int (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, int> GetLastErrMsg;

        [NativeTypeName("int (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, int> GetLastErrJson;

        [NativeTypeName("bool (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, byte> GetCompileVersion;

        [NativeTypeName("bool (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, byte> GetCompileTime;

        [NativeTypeName("bool (*)(char *, int)")]
        public delegate* unmanaged[Cdecl]<sbyte*, int, byte> GetCoreModulePath;
    }

    public unsafe delegate cvAutoTrackContextV1* CreateContextV1Type();
    public unsafe delegate void DestroyContextV1Type(cvAutoTrackContextV1* context);

    //public static unsafe partial class Methods
    //{
    //    [DllImport("", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    //    public static extern cvAutoTrackContextV1* create_cvAutoTrack_context_v1();
    //
    //    [DllImport("", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    //    public static extern void destroy_cvAutoTrack_context_v1(cvAutoTrackContextV1* context);
    //}
}
