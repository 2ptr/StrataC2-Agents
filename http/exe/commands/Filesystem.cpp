//
// Created by jake.otte on 5/12/2025.
//
#include <sstream>
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

std::string CommandHelper::cmd_touch(std::string cmd, const std::vector<std::string>& args) {
    if (args.empty()) return "Error: No file specified.";

    HANDLE hFile = CreateFileA(
        args[0].c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) return "Error: Could not create file.";
    CloseHandle(hFile);
    return "File created.";
}

std::string CommandHelper::cmd_rm(std::string cmd, const std::vector<std::string>& args) {
    if (args.empty()) return "Error: No file specified.";

    if (!DeleteFileA(args[0].c_str())) return "Error: Could not delete file.";
    return "File deleted.";
}

std::string CommandHelper::cmd_cp(std::string cmd, const std::vector<std::string>& args) {
    if (args.size() < 2) return "Error: Source and destination required.";

    if (!CopyFileA(args[0].c_str(), args[1].c_str(), FALSE)) return "Error: Could not copy file.";
    return "File copied.";
}

std::string CommandHelper::cmd_mv(std::string cmd, const std::vector<std::string>& args) {
    if (args.size() < 2) return "Error: Source and destination required.";

    if (!MoveFileA(args[0].c_str(), args[1].c_str())) return "Error: Could not move file.";
    return "File moved.";
}

std::string CommandHelper::cmd_ls(std::string cmd, const std::vector<std::string>& args) {
    std::string path = args.empty() ? "." : args[0];
    std::string cwd = cmd_pwd(cmd, args);
    path += "\\*";

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) return "Error: Could not list directory.";

    std::ostringstream oss;
    oss << "Directory of " << cwd << "\n\n";
    do {
        oss << (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR> " : "      ");
        oss << "\t" << findData.cFileName << "\n";
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return oss.str();
}

std::string CommandHelper::cmd_mkdir(std::string cmd, const std::vector<std::string>& args) {
    if (args.empty()) return "Error: No directory name specified.";

    if (!CreateDirectoryA(args[0].c_str(), NULL)) return "Error: Could not create directory.";
    return "Directory created.";
}

std::string CommandHelper::cmd_rmdir(std::string cmd, const std::vector<std::string>& args) {
    if (args.empty()) return "Error: No directory name specified.";

    if (!RemoveDirectoryA(args[0].c_str())) return "Error: Could not remove directory.";
    return "Directory removed.";
}

std::string CommandHelper::cmd_pwd(std::string cmd, const std::vector<std::string>& args) {
    char buffer[MAX_PATH];
    if (!GetCurrentDirectoryA(MAX_PATH, buffer)) return "Error: Could not get current directory.";
    return std::string(buffer);
}

std::string CommandHelper::cmd_cd(std::string cmd, const std::vector<std::string>& args) {
    if (args.empty()) return "Error: No directory specified.";

    if (!SetCurrentDirectoryA(args[0].c_str())) return "Error: Could not change directory.";
    return "Directory changed to " + args[0];
}