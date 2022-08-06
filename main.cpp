#include <iostream>
#include <Windows.h>
#include <Core.h>
#include <Common/VersionInfo.h>
#include <Common/VMProtect.h>

#include "resource.h"

int main()
{
	VMProtectBeginMutation(__FUNCTION__);

	Core::Initialize();

	VMProtectEnd();
	return 0;
}