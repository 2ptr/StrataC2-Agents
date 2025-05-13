//
// Created by jake.otte on 5/12/2025.
//
#include <windows.h>
#include <string>
#include "CommandHelper.h"

std::string CommandHelper::cmd_cat(std::string cmd, const std::vector<std::string> &args) {
    if (args.empty()) {
        return "Error: No file specified.";
    }

    HANDLE hFile = CreateFileA(
        args[0].c_str(),         // File name
        GENERIC_READ,            // Desired access
        FILE_SHARE_READ,         // Share mode
        NULL,                    // Security attributes
        OPEN_EXISTING,           // Creation disposition
        FILE_ATTRIBUTE_NORMAL,   // Flags and attributes
        NULL);                   // Template file

    if (hFile == INVALID_HANDLE_VALUE) {
        return "Error: Could not open file.";
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        CloseHandle(hFile);
        return "Error: Could not get file size.";
    }

    std::string content;
    content.resize(static_cast<size_t>(fileSize.QuadPart));

    DWORD bytesRead;
    if (!ReadFile(hFile, content.data(), static_cast<DWORD>(fileSize.QuadPart), &bytesRead, NULL)) {
        CloseHandle(hFile);
        return "Error: Could not read file.";
    }

    CloseHandle(hFile);
    return content;
}