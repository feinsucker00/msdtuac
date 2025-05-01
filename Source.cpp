#include "pch.h"
#include <iostream>
#include <windows.h>
void executor()
{

        STARTUPINFO si = { sizeof(STARTUPINFO) };
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOWNORMAL;  // Ensures the console window is visible

        PROCESS_INFORMATION pi;

        if (CreateProcess(
            L"C:\\Windows\\System32\\cmd.exe", // Application path
            NULL,                            // Command line args
            NULL,                            // Process handle not inheritable
            NULL,                            // Thread handle not inheritable
            FALSE,                           // Inherit handles
            CREATE_NEW_CONSOLE,              // Ensures a new console window
            NULL,                            // Use parent's environment
            NULL,                            // Use parent's starting directory
            &si,                             // Pointer to STARTUPINFO
            &pi)                             // Pointer to PROCESS_INFORMATION
            )
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            std::cerr << "Failed to start cmd.exe. Error: " << GetLastError() << std::endl;
        }
    }


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        executor();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
