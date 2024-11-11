// Programa 1 - Versão Windows
#include <windows.h>
#include <stdio.h>

int value = 5;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR cmdLine[] = TEXT("child_process.exe");  
    char envVar[32];
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    sprintf_s(envVar, sizeof(envVar), "VALUE=%d", value);
    _putenv(envVar);

    if (!CreateProcess(
        NULL,           
        cmdLine,        
        NULL,           
        NULL,           
        FALSE,          
        0,             
        NULL,          
        NULL,          
        &si,           
        &pi)           
        ) {
        fprintf(stderr, "Criação do processo falhou (%d).\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("PARENT: value = %d\n", value); // LINHA A
    return 0;
}