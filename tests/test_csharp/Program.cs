using System.Text;
namespace test_csharp
{
    internal class Program
    {
        static unsafe void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

            var loader = new cvAutoTrackInterface.CustomLoader();
            var inface = "C:\\Users\\YuSuiXian\\source\\repos\\cvAutoTrack\\build\\bin\\Release\\cvAutoTrack.dll";
            var deps = "C:\\Users\\YuSuiXian\\source\\repos\\cvAutoTrack.Inface\\build\\bin\\Debug\\core\\deps";

            if (!loader.Load(inface, deps))
            {
                //Debug.LogError("Load failed");
                return;
            }

            var context = loader.CreateContext();
            if (context == null)
            {
                //Debug.LogError("CreateContext failed");
                return;
            }
            double x = 0;
            double y = 0;
            int z = 0;

            var ret = context->GetPositionOfMap(&x, &y, &z);
            Console.WriteLine(ret);
            if (ret == 0)
            {
                var error_code = context->GetLastErr();
                Console.WriteLine(error_code);
                sbyte* error_msg = stackalloc sbyte[1024];
                context->GetLastErrMsg(error_msg, 1024);
                string msg = new string(error_msg);
                Console.WriteLine(msg);
                // to utf8 from gbk
                byte[] bytes = Encoding.Convert(Encoding.UTF8, Encoding.GetEncoding("gbk"), Encoding.Default.GetBytes(msg));
                Console.WriteLine(Encoding.UTF8.GetString(bytes));
            }


            context->DebugCapture();
            context->UnInitResource();

            loader.DestroyContext();
            loader.Unload();

            Console.WriteLine("Hello, World!");
        }

    }
}
