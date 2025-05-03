#pragma once

class config
{
public:
	static bool enableConsole;
	static bool enableFileAccessLog;
	static bool enableLooseFileLoad;

	static bool init();
};