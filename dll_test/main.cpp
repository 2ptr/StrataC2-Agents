#include <windows.h>

int main() {
    HMODULE dll = LoadLibraryA("strata-dll.dll");
    if (dll == NULL) {
        MessageBoxA(NULL, "DLL Load Failed", "Test", MB_OK);
        return 1;
    }

    using Fn = void(*)();
    Fn entry = (Fn)GetProcAddress(dll, "RunAgent");
    if (entry) entry();
    return 0;
}
