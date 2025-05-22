#include <windows.h>
#include <stdio.h>

int main() {
    FILE* f = fopen("strata-dll.bin", "rb");
    if (!f) {
        printf("Failed to open loader.bin\n");
        return 1;
    }

    // Get file size
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (filesize <= 0) {
        printf("Invalid loader.bin size\n");
        fclose(f);
        return 1;
    }

    // Allocate buffer to hold shellcode
    unsigned char* shellcode = (unsigned char*)VirtualAlloc(
        NULL,
        filesize,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE);

    if (!shellcode) {
        printf("VirtualAlloc failed\n");
        fclose(f);
        return 1;
    }

    // Read shellcode into buffer
    size_t read = fread(shellcode, 1, filesize, f);
    fclose(f);

    if (read != filesize) {
        printf("Failed to read full shellcode\n");
        VirtualFree(shellcode, 0, MEM_RELEASE);
        return 1;
    }

    // Cast shellcode buffer to function pointer and call it
    void (*sc_func)() = (void (*)())shellcode;
    sc_func();

    // Free memory after execution (optional, shellcode may not return)
    VirtualFree(shellcode, 0, MEM_RELEASE);

    return 0;
}
