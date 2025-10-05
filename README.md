
```
cd src
```

```
g++ -shared -o build\serialib_native.dll main.cpp serialib.cpp
```

```C#
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
```
