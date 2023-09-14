#include <stdio.h>
#include "../dynabuf.h"

int main(int argc, char *argv[]) {
    DynamicBuffer(int) *buffer = newDynamicBuf(int);
    printErr(initDynamicBuf(int, buffer));

    printf("%d units allocated to 'buffer'\n", buffer->capacity);
    for (int addr = 0; addr < buffer->capacity; ++addr) {
        printf("%d\n", readDynamicBuf(int, buffer, addr));
    }

    printErr(writeDynamicBuf(int, buffer, 5, 69420));

    printf("%d units allocated to 'buffer'\n", buffer->capacity);
    for (int addr = 0; addr < buffer->capacity; ++addr) {
        printf("%d\n", readDynamicBuf(int, buffer, addr));
    }

    printErr(writeDynamicBuf(int, buffer, 9, 2020));

    printf("\n%d units allocated to 'buffer'\n", buffer->capacity);
    for (int addr = 0; addr < buffer->capacity; ++addr) {
        printf("%d\n", readDynamicBuf(int, buffer, addr));
    }

    clearDynamicBuf(int, buffer, 0);

    printf("\n%d units allocated to 'buffer'\n", buffer->capacity);
    for (int addr = 0; addr < buffer->capacity; ++addr) {
        printf("%d\n", readDynamicBuf(int, buffer, addr));
    }
}