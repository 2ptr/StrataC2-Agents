//
// Created by jake.otte on 5/12/2025.
//

#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <string>
#include <vector>

class CommandHelper {
public:
    static std::string handleCommand(const std::string &cmd, const std::vector<std::string> &args);

    // Filesystem
    static std::string cmd_cat(std::string cmd, const std::vector<std::string> &args);

    // Execution
    static std::string cmd_shell(std::string cmd, const std::vector<std::string> &args);
};



#endif //COMMANDHELPER_H
