#pragma once

#include "../WinMain.h"

#include <winioctl.h>

class Driver
{
private:
	HANDLE hDriver;
	std::string DeviceName;
	std::string DriverPath;
	std::string DriverName;

	ULONG ProcessId;
	HANDLE ProcessHandle;

public:
	Driver(std::string DriverName, std::string DeviceName);
	Driver(std::string DriverPath, std::string DriverName, std::string DeviceName);
	~Driver();

	void SetDriverPath(std::string DriverPath);

	bool IsDriverCreated();
	bool CreateDriver();
	bool IsDriverStarted();
	bool StartDriver();

	int Load();
	void Unload();
	void Delete();
	BOOL Connect();
};