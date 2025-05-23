#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <windows.h>

// Correct way for constants
inline int SLEEP = 1000;

const LPCWSTR USER_AGENT = L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36";

constexpr LPCWSTR CONTENT_TYPE = L"Content-Type: application/json\r\n";
constexpr LPCWSTR POST_VERB = L"POST";

// Correct way for map
const std::map<std::wstring, int> CALLBACKS = {
    {L"127.0.0.1", 443},
    {L"localhost", 443}
};


#endif // CONFIG_H
