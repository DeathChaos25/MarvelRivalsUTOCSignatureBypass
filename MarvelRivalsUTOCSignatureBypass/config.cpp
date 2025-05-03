#include "pch.h"
#include "config.h"

bool config::enableConsole;
bool config::enableFileAccessLog;
bool config::enableLooseFileLoad;

bool config::init()
{
    toml::table config;
    std::string fileString = "";

    try
    {
        std::ifstream file("config.toml");
        std::string str;
        while (std::getline(file, str))
            fileString += str + "\n";

        config = toml::parse(fileString);
    }
    catch (std::exception& exception)
    {
        char text[1024];
        sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
        MessageBoxA(nullptr, text, "File Access Log", MB_OK | MB_ICONERROR);
    }

    enableConsole = config["Enable_Console"].value_or(false);
    enableFileAccessLog = config["File_Access_Logging"].value_or(false);
    enableLooseFileLoad = config["Loose_File_Loading"].value_or(false);

    return true;
}