#include "./Driver.h"

Driver::Driver(std::string DriverName, std::string DeviceName)
{
	this->DriverName = DriverName;
	this->DeviceName = DeviceName;
}

Driver::Driver(std::string DriverPath, std::string DriverName, std::string DeviceName)
{
	this->DriverPath = DriverPath;
	this->DriverName = DriverName;
	this->DeviceName = DeviceName;
}

Driver::~Driver()
{
	this->hDriver = 0x0;
	this->DriverPath = "";
	this->DriverName = "";
	this->DeviceName = "";
}

void Driver::SetDriverPath(std::string DriverPath)
{
	this->DriverPath = DriverPath;
}

bool Driver::IsDriverCreated()
{
	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCManager <= 0)
	{
		return false;
	}

	SC_HANDLE hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_ALL_ACCESS);
	if (hService <= 0)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	CloseServiceHandle(hSCManager);
	return true;
}

bool Driver::CreateDriver()
{
	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCManager <= 0)
	{
		return false;
	}

	SC_HANDLE hService = CreateServiceA(hSCManager, this->DriverName.c_str(), this->DriverName.c_str(), SERVICE_START, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, this->DriverPath.c_str(), nullptr, nullptr, nullptr, nullptr, nullptr);
	if (hService == 0x0 || hService == INVALID_HANDLE_VALUE)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	CloseServiceHandle(hSCManager);
	return true;
}

bool Driver::IsDriverStarted()
{
	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCManager <= 0)
	{
		return false;
	}

	SC_HANDLE hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_ALL_ACCESS);
	if (hService <= 0)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	SERVICE_STATUS_PROCESS ssp;
	DWORD dwBytesNeeded;
	if (!QueryServiceStatusEx(
		hService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	if (ssp.dwCurrentState == SERVICE_RUNNING)
	{
		return true;
	}

	CloseServiceHandle(hSCManager);
	return false;
}

bool Driver::StartDriver()
{
	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCManager <= 0)
	{
		return false;
	}

	SC_HANDLE hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_ALL_ACCESS);
	if (hService <= 0)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	if (!StartServiceA(hService, NULL, nullptr))
	{
		CloseServiceHandle(hSCManager);
		return false;
	}

	return true;
}

int Driver::Load()
{
	this->Unload();

	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_CREATE_SERVICE);
	if (hSCManager == 0x0 || hSCManager == INVALID_HANDLE_VALUE) return FALSE;

	SC_HANDLE hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_START);
	if (hService == 0x0 || hService == INVALID_HANDLE_VALUE)
	{
		hService = CreateServiceA(hSCManager, this->DriverName.c_str(), this->DriverName.c_str(), SERVICE_START, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, this->DriverPath.c_str(), nullptr, nullptr, nullptr, nullptr, nullptr);
		if (hService == 0x0 || hService == INVALID_HANDLE_VALUE)
		{
			CloseServiceHandle(hSCManager);
			return -1;
		}
	}

	bool bStartService = StartServiceA(hService, NULL, nullptr);
	if (!bStartService)
	{
		CloseServiceHandle(hService);
		hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_START | SERVICE_CHANGE_CONFIG);
		bool bChangeServiceConfig = ChangeServiceConfigA(hService, SERVICE_NO_CHANGE, SERVICE_DEMAND_START, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
		if (bChangeServiceConfig)
		{
			bStartService = StartServiceA(hService, NULL, nullptr);
			if (!bStartService)
			{
				this->Unload();
				return -1;
			}
		}
	}

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hService);
	return true;
}

void Driver::Unload()
{
	SC_HANDLE hSCManager = OpenSCManagerA(0, 0, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = OpenServiceA(hSCManager, this->DriverName.c_str(), SERVICE_ALL_ACCESS);

	SERVICE_STATUS ServiceStatus;
	ControlService(hService, SERVICE_CONTROL_STOP, &ServiceStatus);
	DeleteService(hService);

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hService);
}

void Driver::Delete()
{
	this->Unload();
	_unlink(this->DriverPath.c_str());
}

BOOL Driver::Connect()
{
	this->hDriver = CreateFileA(this->DeviceName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (this->hDriver == 0x0 || this->hDriver == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	return TRUE;
}