#include <vector>
#include "CommandHelper.h"


std::string CommandHelper::handleCommand(const std::string &cmd, const std::vector<std::string> &args) {
    // Management
    if (cmd == "die") { return cmd_die(cmd, args); }
    if (cmd == "sleep") { return cmd_sleep(cmd, args); }

    // Filesystem
    if (cmd == "cat") { return cmd_cat(cmd, args); }
    if (cmd == "touch") { return cmd_touch(cmd, args); }
    if (cmd == "rm") { return cmd_rm(cmd, args); }
    if (cmd == "cp") { return cmd_cp(cmd, args); }
    if (cmd == "mv") { return cmd_mv(cmd, args); }
    if (cmd == "ls") { return cmd_ls(cmd, args); }
    if (cmd == "mkdir") { return cmd_mkdir(cmd, args); }
    if (cmd == "rmdir") { return cmd_rmdir(cmd, args); }
    if (cmd == "pwd") { return cmd_pwd(cmd, args); }
    if (cmd == "cd") { return cmd_cd(cmd, args); }

    // Execution
    if (cmd == "shell") { return cmd_shell(cmd, args); }
    return "Command not implemented.";
}
