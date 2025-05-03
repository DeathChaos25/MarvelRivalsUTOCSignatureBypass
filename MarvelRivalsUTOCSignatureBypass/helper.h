#pragma once
#include <regex>

/// Formats file path for logging.
inline const wchar_t* processFilePath(const wchar_t* filePath)
{
    std::wstring newPath = std::regex_replace(filePath, std::wregex(L"\\./"), L"/");
    newPath = std::regex_replace(newPath, std::wregex(L"(/+)"), L"/");
    return newPath.c_str();
}