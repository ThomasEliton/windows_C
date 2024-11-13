#include <windows.h> // Inclui a biblioteca do Windows para usar funções de gerenciamento de processos
#include <stdio.h>   // Biblioteca padrão de entrada/saída

int value = 5; // Define uma variável global `value` com o valor 5

int main() {
    STARTUPINFO si;               // Estrutura que armazena informações sobre a aparência da janela do processo criado
    PROCESS_INFORMATION pi;       // Estrutura que recebe informações sobre o novo processo
    TCHAR cmdLine[] = TEXT("child_process.exe"); // Comando para o executável do processo filho
    char envVar[32];              // Array para armazenar a variável de ambiente

    ZeroMemory(&si, sizeof(si));  // Zera os bytes da estrutura `si` para garantir que todos os valores estejam iniciados
    si.cb = sizeof(si);           // Define o tamanho da estrutura `si`
    ZeroMemory(&pi, sizeof(pi));  // Zera os bytes da estrutura `pi`

    // Define uma variável de ambiente chamada "VALUE" com o valor da variável `value`
    sprintf_s(envVar, sizeof(envVar), "VALUE=%d", value); 
    _putenv(envVar);              // Define `envVar` como variável de ambiente

    // Cria um novo processo para executar "child_process.exe"
    if (!CreateProcess(
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
        fprintf(stderr, "Criação do processo falhou (%d).\n", GetLastError()); // Erro caso a criação do processo falhe
        return 1; // Retorna 1 para indicar falha na criação do processo
    }

    // Espera até que o processo filho termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Fecha os identificadores de processo e de thread para liberar recursos do sistema
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Imprime o valor da variável `value` no processo pai (LINHA A)
    printf("PARENT: value = %d\n", value);
    return 0; // Encerra o programa pai
}
