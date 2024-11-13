#include <windows.h> // Inclui a biblioteca do Windows (necessária para o ambiente Windows, mas não usada diretamente neste programa)
#include <stdio.h>    // Biblioteca padrão de entrada/saída (não é utilizada diretamente neste programa, mas pode ser útil para debug)
#include <stdlib.h>   // Inclui funções de conversão e manipulação de ambiente

int main() {
    // Obtém o valor da variável de ambiente "VALUE" como uma string
    char* valueStr = getenv("VALUE");

    // Verifica se a variável de ambiente foi encontrada
    if (valueStr != NULL) {
        // Converte o valor da string `valueStr` para um inteiro
        int value = atoi(valueStr);

        // Incrementa `value` em 15
        value += 15;

        // Note que o valor incrementado não é usado ou exibido após essa linha
    }

    return 0; // Encerra o programa com um código de sucesso
}
