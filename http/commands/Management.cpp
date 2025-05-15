#include "../conf/Config.h"
#include <string>
#include "CommandHelper.h"

std::string CommandHelper::cmd_sleep(const std::string& cmd, const std::vector<std::string> &args) {
    if (!args.empty()) {
        try {
            const int sleep_time = std::stoi(args[0]) * 1000;
            SLEEP = sleep_time;
        } catch (std::exception& e) {
            return "Error: Invalid sleep time.";
        }
    }
    return "Sleep time set to " + std::to_string(SLEEP) + "ms.";
}

std::string CommandHelper::cmd_die(const std::string& cmd, const std::vector<std::string> &args) {
    exit(0);
    return "";
}