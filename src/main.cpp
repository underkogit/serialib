#include <iostream>
#include "serialib.h"

#define SERIALIB_API __declspec(dllexport)

#if defined(_WIN32) || defined(_WIN64)
#define SERIAL_PORT "\\\\.\\COM1"
#endif
#if defined(__linux__) || defined(__APPLE__)
#define SERIAL_PORT "/dev/ttyACM0"
#endif

extern "C"
{
    SERIALIB_API serialib *createA()
    {

        return new serialib();
    }

    SERIALIB_API char openDeviceA(serialib *serialib, const char *Device, const unsigned int Bauds)
    {

        return serialib->openDevice(Device, Bauds);
    }

    SERIALIB_API char writeStringA(serialib *serialib, const char *String)
    {
        return serialib->writeString(String);
    }

    SERIALIB_API char readStringA(serialib *serialib, char *Buffer, char EndChar, unsigned int MaxSize, unsigned int Timeout)
    {
        return serialib->readString(Buffer, EndChar, MaxSize, Timeout);
    }

    SERIALIB_API void closeDeviceA(serialib *serialib)
    {
        serialib->closeDevice();
    }
}
