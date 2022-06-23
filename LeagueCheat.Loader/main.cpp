#include <iostream>
#include <Windows.h>

#include "./Core.h"
#include "./resource.h"

int main()
{
	VMProtectBeginUltra(__FUNCTION__);

	if (!Core::Initialize())
	{
		Console::Pause();
		return 0;
	}

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Core::InjectThread, 0, 0, 0);

	while (true)
	{
		Sleep(10000);
	}

	Console::Pause();

	VMProtectEnd();
	return 0;
}