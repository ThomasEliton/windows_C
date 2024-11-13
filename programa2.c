#include <windows.h> // Inclui a biblioteca do Windows para usar funções de criação e manipulação de processos
#include <stdio.h>    // Biblioteca padrão de entrada/saída para uso da função printf

// Função que cria um processo filho
void CreateChildProcess() {
    STARTUPINFO si;               // Estrutura que armazena informações sobre a aparência e comportamento do processo criado
    PROCESS_INFORMATION pi;       // Estrutura que recebe informações sobre o novo processo (como identificadores)
    TCHAR cmdLine[] = TEXT("child_process.exe"); // Comando para o executável do processo filho

    ZeroMemory(&si, sizeof(si));  // Inicializa a estrutura `si` com zeros
    si.cb = sizeof(si);           // Define o tamanho da estrutura `si`
    ZeroMemory(&pi, sizeof(pi));  // Inicializa a estrutura `pi` com zeros

    // Cria um novo processo para executar "child_process.exe"
    if (CreateProcess(
        NULL,            // Nome do módulo (NULL pois usamos `cmdLine` diretamente)
        cmdLine,         // Caminho para o executável do processo filho
        NULL,            // Atributos de segurança para o processo
        NULL,            // Atributos de segurança para o thread principal
        FALSE,           // Herança de identificadores desativada
        0,               // Nenhuma criação de bandeira especial (flags)
        NULL,            // Variáveis de ambiente (NULL usa as variáveis do processo atual)
        NULL,            // Diretório atual do novo processo (NULL mantém o atual)
        &si,             // Ponteiro para a estrutura STARTUPINFO
        &pi              // Ponteiro para a estrutura PROCESS_INFORMATION
        )) {
        // Caso a criação do processo tenha sido bem-sucedida, os identificadores de processo e thread são fechados
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main() {
    // Chama a função para criar três processos filhos
    CreateChildProcess();
    CreateChildProcess();
    CreateChildProcess();

    // Exibe o ID do processo atual
    printf("Processo criado. PID: %d, PPID: %d\n", 
           GetCurrentProcessId(),   // Retorna o ID do processo atual (PID)
           GetCurrentProcessId());  // Exibe novamente o mesmo ID, pois o PPID (Process Parent ID) não é obtido diretamente no Windows

    return 0; // Encerra o programa principal
}
