#include "Core.h"

bool Core::Initialize()
{
	Console::Setup(VMPSTRA("Loader"));

	CHAR szBuffer[MAX_PATH];
	GetFullPathNameA(VMPSTRA("Loader_old_3304.exe"), sizeof(szBuffer), szBuffer, nullptr);
	std::string oldLoaderPath = szBuffer;
	if (PathFileExistsA(oldLoaderPath.c_str()))
	{
		_unlink(oldLoaderPath.c_str());
	}

	CHAR szExeFileName[MAX_PATH];
	GetModuleFileNameA(NULL, szExeFileName, sizeof(szExeFileName));
	std::string fileName = Utilities::GetFileName(szExeFileName);

	if (Utilities::IsProcessRunning(Utilities::StringToWString(fileName).c_str()))
	{
		Console::Log(VMPSTRA("Process is already running"), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}



	return true;
}