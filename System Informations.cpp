#include <windows.h> 
#include <iostream> 
#include <dxgi.h> 

#pragma comment(lib, "dxgi.lib") 
using namespace std;

int main()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);

    SYSTEM_INFO info;
    GetSystemInfo(&info);

    ULARGE_INTEGER freeBytes, totalBytes;

    while (true) {
        IDXGIFactory* factory = nullptr;

        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

        IDXGIAdapter* adapter = nullptr;

        system("cls");

        if (GlobalMemoryStatusEx(&memInfo)) {
            cout << "RAM Information\n";
            cout << "------------------------\n";

            cout << "Total RAM: " << memInfo.ullTotalPhys / 1024 / 1024 / 1024 << " GB\n";
            cout << "Available RAM: " << memInfo.ullAvailPhys / 1024 / 1024 / 1024 << " GB\n";
            cout << "Memory Usage: " << memInfo.dwMemoryLoad << "%\n";
        }

        else
        {
            cout << "Error!\n";
        }

        cout << "CPU Information\n";
        cout << "------------------------\n";
        cout << "CPU Cores: " << info.dwNumberOfProcessors << endl;

        if (GetDiskFreeSpaceExA("C:\\", &freeBytes, &totalBytes, NULL))
        {
            cout << "Disk Information\n";
            cout << "------------------------\n";
            cout << "Disk C:\n";
            cout << "Total: " << totalBytes.QuadPart / 1024 / 1024 / 1024 << " GB\n";
            cout << "Free: " << freeBytes.QuadPart / 1024 / 1024 / 1024 << " GB\n";
        }

        if (factory->EnumAdapters(0, &adapter) == S_OK)
        {
            DXGI_ADAPTER_DESC desc;
            adapter->GetDesc(&desc);
            cout << "GPU Information\n";
            cout << "------------------------\n";
            wcout << L"GPU: " << desc.Description << endl;

            adapter->Release();
        }

        factory->Release();
        Sleep(5000);
    }
    system("pause");
    return 0;
}
