//
// Created by jake.otte on 5/12/2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <map>
#include <vector>
#include <string>

constexpr int SLEEP = 1000;
const std::map<std::wstring, int> CALLBACKS = { {L"127.0.0.1", 443}, {L"localhost", 443} };
const std::wstring USER_AGENT = L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36";
constexpr LPCWSTR CONTENT_TYPE = L"Content-Type: application/json\r\n";
constexpr LPCWSTR POST_VERB = L"POST";

#endif //CONFIG_H
