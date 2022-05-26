#include "./Core.h"

extern Utilities* Utils;

void Core::ExitFailed(const char* log)
{
	MessageBoxA(0, log, xorstr_("Error"), MB_ICONERROR);
	ExitProcess(-1);
}

void Core::CreateResources()
{
	CHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPathA(0, szProgramFiles, CSIDL_PROGRAM_FILES, FALSE);
	std::string rootPath = szProgramFiles;

	rootPath += "\\LeagueCheat";
	CreateDirectoryA(rootPath.c_str(), 0);
	
	std::string resPath = rootPath + "\\Resources";
	CreateDirectoryA(resPath.c_str(), 0);

	std::string scriptsPath = rootPath + "\\Scripts";
	CreateDirectoryA(scriptsPath.c_str(), 0);

	this->RobotoPath = resPath + "\\Roboto.ttf";
	if (!PathFileExistsA(this->RobotoPath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)Roboto_RawBinary, sizeof(Roboto_RawBinary), this->RobotoPath, CREATE_NEW);
	}

	this->FontAwesomePath = resPath + "\\FontAwesome.ttf";
	if (!PathFileExistsA(this->FontAwesomePath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)FontAwesome_RawBinary, sizeof(FontAwesome_RawBinary), this->FontAwesomePath, CREATE_NEW);
	}

	this->ArialUniPath = resPath + "\\ArialUni.ttf";

	this->ConfigPath = rootPath + "\\LeagueCheat.Config.ini";
	if (!PathFileExistsA(this->ConfigPath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)0, 0, this->ConfigPath, CREATE_NEW);
	}

	this->CorePath = rootPath + "\\LeagueCheat.Core.dll";

	this->ServicePath = rootPath + "\\LeagueCheat.Service.sys";
	if (!PathFileExistsA(this->ServicePath.c_str()))
	{
		//Utils->WriteDataToFile((UCHAR*)Xtreme_RawBinary, sizeof(Xtreme_RawBinary), this->XtremePath, CREATE_NEW);
	}
}