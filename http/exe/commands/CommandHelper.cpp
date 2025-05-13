//
// Created by jake.otte on 5/12/2025.
//

#include "CommandHelper.h"

#include <vector>

std::string CommandHelper::handleCommand(const std::string &cmd, const std::vector<std::string> &args) {
    if (cmd == "shell") { return cmd_shell(cmd, args); }
    if (cmd == "cat") { return cmd_cat(cmd, args); }
    return "Command not implemented.";
}

