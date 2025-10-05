using SerialIO.Helper;


Random R = new Random();
using (SerialPortManager serialPort = new SerialPortManager(@"\\.\COM10", 115200))
{
    uint rate = serialPort.MaxRateTesting();
    
    while (true)
    {
    

        serialPort.Write($"{R.Next(0,1000)},3,5,1,3,{R.Next(0,1000)}");

        string response = serialPort.Read('\n', 256, rate);
         
        Console.WriteLine(response);

        // Thread.Sleep(1000);
    }
}