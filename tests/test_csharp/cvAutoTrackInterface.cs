using cvAutoTrackNative;
using System.Runtime.InteropServices;
namespace cvAutoTrackInterface
{
    public unsafe delegate cvAutoTrackContextV1* CreateContextType();
    public unsafe delegate void DestroyContextType(cvAutoTrackContextV1* context);

    public class CustomLoader
    {
        public bool IsLoaded { get; private set; }
        public unsafe cvAutoTrackContextV1* Context { get; private set; }

        private IntPtr Handle;
        private IntPtr createFunc;
        private IntPtr destroyFunc;

        public CustomLoader()
        {
            IsLoaded = false;
            Handle = IntPtr.Zero;
        }

        public bool Load(string core, string deps_dir)
        {
            try
            {
                if (IsLoaded) return false;

                Handle = LoadLibrary(core);
                if (Handle == IntPtr.Zero) return false;

                var create = GetProcAddress(Handle, "create_cvAutoTrack_context_v1");
                if (create == IntPtr.Zero) return false;
                var destroy = GetProcAddress(Handle, "destroy_cvAutoTrack_context_v1");
                if (destroy == IntPtr.Zero) return false;

                createFunc = create;
                destroyFunc = destroy;

                IsLoaded = true;
                return true;
            }
            catch
            {

            }
            return false;
        }

        public void Unload()
        {
            if (!IsLoaded) return;
            if (Handle != IntPtr.Zero)
            {
                IsLoaded = false;
                FreeLibrary(Handle);
                return;
            }
            IsLoaded = false;
        }

        public unsafe cvAutoTrackContextV1* CreateContext()
        {
            if (!IsLoaded) return null;
            if (Context != null) return Context;
            Context = Marshal.GetDelegateForFunctionPointer<CreateContextV1Type>(createFunc)();
            return Context;
        }

        public unsafe void DestroyContext()
        {
            if (!IsLoaded) return;
            if (Context == null) return;
            var func = Marshal.GetDelegateForFunctionPointer<DestroyContextType>(destroyFunc);
            func(Context);
            Context = null;
        }


        #region Win API
        [DllImport("kernel32.dll")]
        private extern static IntPtr LoadLibrary(string path);

        [DllImport("kernel32.dll")]
        private extern static IntPtr GetProcAddress(IntPtr lib, string funcName);

        [DllImport("kernel32.dll")]
        private extern static bool FreeLibrary(IntPtr lib);
        #endregion
    }
}


