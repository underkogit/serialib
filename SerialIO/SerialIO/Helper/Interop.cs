using System.Runtime.InteropServices;

namespace SerialIO.Helper;

public static class Interop
{
    public const string Lib = "serialib_native.dll";


    [DllImport(Lib, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr createA();

    // Define the import for the openDeviceA function
    [DllImport(Lib, CallingConvention = CallingConvention.Cdecl)]
    public static extern char openDeviceA(IntPtr serialibObj, string device, uint bauds);

    // Define the import for the writeStringA function
    [DllImport(Lib, CallingConvention = CallingConvention.Cdecl)]
    public static extern char writeStringA(IntPtr serialibObj, string str);

    // Define the import for the readStringA function
    [DllImport(Lib, CallingConvention = CallingConvention.Cdecl)]
    public static extern char readStringA(IntPtr serialibObj, byte[] buffer, char endChar, uint maxSize, uint timeout);

    // Define the import for the closeDeviceA function
    [DllImport(Lib, CallingConvention = CallingConvention.Cdecl)]
    public static extern void closeDeviceA(IntPtr serialibObj);
}