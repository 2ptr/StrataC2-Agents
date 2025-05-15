#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <string>
#include <vector>

class CommandHelper {
public:
    static std::string handleCommand(const std::string &cmd, const std::vector<std::string> &args);

    // Management
    static std::string cmd_die(const std::string& cmd, const std::vector<std::string> &args);
    static std::string cmd_sleep(const std::string& cmd, const std::vector<std::string> &args);

    // Filesystem
    static std::string cmd_cat(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_touch(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_rm(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_cp(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_mv(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_ls(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_mkdir(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_rmdir(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_pwd(std::string cmd, const std::vector<std::string> &args);
    static std::string cmd_cd(std::string cmd, const std::vector<std::string> &args);

    // Execution
    static std::string cmd_shell(std::string cmd, const std::vector<std::string> &args);
};



#endif //COMMANDHELPER_H
