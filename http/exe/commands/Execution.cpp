#include <windows.h>
#include <string>
#include "CommandHelper.h"

std::string CommandHelper::cmd_shell(std::string cmd, const std::vector<std::string> &args) {
    std::string full_args;
    for (const auto& s : args) { full_args += s; }
    full_args = "cmd.exe /c " + full_args;
    system(full_args.c_str());
    return "Did shell command.";
}