using System.Text;

namespace SerialIO.Helper;

public class SerialPortManager : IDisposable
{
    private IntPtr _serialObj;
    private string _strTesting = "[Testing];";
    private Random R = new Random();
    public SerialPortManager(string portName, uint baudRate , string testing = "[Testing];")
    {
        _serialObj = Interop.createA();
        _strTesting = testing;
        if (Interop.openDeviceA(_serialObj, portName, baudRate) != 1)
        {
            throw new InvalidOperationException("Failed to open serial device.");
        }
    }

    public uint MaxRateTesting(int maxCount = 4, uint size = 200, uint maxSize = 256 )
    {
        uint maxRate = 100;
        int count = 0;
        while (true)
        {
            this.Write(_strTesting);

            string response = this.Read('\n', maxSize, maxRate).Replace("\r\n" , "");
            Console.WriteLine($"MaxRate: {maxRate} := {response}");
            if (response.EndsWith(";") )
            {
                if (count >= maxCount)
                {
                    return maxRate;
                }

                count++;
            }
            else
            {
                maxRate += size;
            }
            
        }

        return maxRate;
    }
    
    public void Write(string message)
    {

        Interop.writeStringA(_serialObj, message);

    }

    public string Read(char endChar, uint maxSize, uint timeout)
    {
        byte[] buffer = new byte[maxSize];
        char result = Interop.readStringA(_serialObj, buffer, endChar, maxSize, timeout);

       
        return Encoding.UTF8.GetString(buffer);
    }

    public void Close()
    {
        Interop.closeDeviceA(_serialObj);
    }

    public void Dispose()
    {
        Close();
    }
}