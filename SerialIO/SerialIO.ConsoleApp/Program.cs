using SerialIO.Helper;


Random R = new Random();
using (SerialPortManager serialPort = new SerialPortManager(@"\\.\COM10", 115200))
{
    //uint rate = serialPort.MaxRateTesting();
    serialPort.Write($"{R.Next(0,255)},{R.Next(0,255)},{R.Next(0,255)},0,0,50");
    Thread.Sleep(1100);
    int c = 0;
    while (true)
    {
        

        serialPort.Write($"{R.Next(0,255)},{R.Next(0,255)},{R.Next(0,255)},255,0,{c}");
        
        Thread.Sleep(1100);
       
        //
        // string response = serialPort.Read('\n', 256, 1100);
        //  
        // Console.WriteLine(response);
        c++;
        Console.WriteLine(c);
        if (c > 24)
            c = 0;
        // Thread.Sleep(1000);
    }
}