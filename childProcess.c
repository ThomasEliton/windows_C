#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char* valueStr = getenv("VALUE");
    if (valueStr != NULL) {
        int value = atoi(valueStr);
        value += 15;
    }
    return 0;
}