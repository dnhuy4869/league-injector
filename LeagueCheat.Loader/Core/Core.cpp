#include "./Core.h"

void Core::ExitFailed(const char* log)
{
	MessageBoxA(0, log, xorstr_("Error"), MB_ICONERROR);
	ExitProcess(-1);
}