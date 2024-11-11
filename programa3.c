// Programa 3 - Versão Windows
#include <windows.h>
#include <stdio.h>

void CreateChildProcess() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR cmdLine[] = TEXT("child_process.exe");

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        CreateChildProcess();
    }

    printf("Processo criado. PID: %d, PPID: %d\n", 
           GetCurrentProcessId(), 
           GetCurrentProcessId());

    return 0;
}