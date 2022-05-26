#include "./Menu.h"
#include "../Core/Core.h"

extern class Core* Core;
extern class D3DX9* D3DX9;
extern class Driver* Driver;
extern Utilities* Utils;

void Menu::RenderConsole()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(this->Width, this->Height));
	ImGui::Begin(
		"###consoleWindow",
		0,
		ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus
	);

	ImDrawList* pImDraw = ImGui::GetForegroundDrawList();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();

	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5) - 20, windowPos.y + 16),
		6,
		ImColor(250, 91, 75),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5), windowPos.y + 16),
		6,
		ImColor(255, 191, 56),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5) + 20, windowPos.y + 16),
		6,
		ImColor(108, 240, 83),
		360
	);

	ImGui::SetCursorPos(ImVec2(15, 32));
	ImGui::BeginChild(
		"###menuConsole",
		ImVec2(this->Width - 30.0f, this->Height - 46.0f),
		false,
		ImGuiWindowFlags_AlwaysVerticalScrollbar
	);

	if (ImGui::BeginTable("###tblConsole", 3))
	{
		ImGui::TableSetupColumn("###col1", ImGuiTableColumnFlags_WidthFixed, 4.0f);
		ImGui::TableSetupColumn("###col2");
		ImGui::TableSetupColumn("###col3", ImGuiTableColumnFlags_WidthFixed, 4.0f);

		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		ImGui::TableNextColumn();

		for (CONSOLE_MESSAGE message : this->ConsoleMessages)
		{
			ImGui_Ex::TextWrappedColored(message.color, message.message.c_str());
		}

		ImGui::TableNextColumn();

		ImGui::EndTable();
	}

	if (this->IsConsoleScroll == true)
	{
		ImGui::SetScrollHereY(1.0f);
		this->IsConsoleScroll = false;
	}

	ImGui::EndChild();

	ImGui::End();
}

void Menu::HandleConsole()
{
	this->Print("Checking core...", D3DX9->Color.Orange400);
	Core->CorePath = "C:\\root_folder\\projects\\league_of_legends\\current_projects\\LeagueCheat\\LeagueCheat.Core\\Release\\LeagueCheat.Core.dll";

	this->Print("Checking service...", D3DX9->Color.Orange400);
	Core->ServicePath = "C:\\Users\\dnhuy\\Desktop\\Nvidia10.sys";

	Driver->SetDriverPath(Core->ServicePath);

	if (!Driver->IsDriverCreated())
	{
		this->Print("Service is not exist, creating new...", D3DX9->Color.Orange400);
		if (!Driver->CreateDriver())
		{
			this->Print("CreateServiceA failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
			return;
		}
	}
	else
	{
		this->Print("Service is already exist", D3DX9->Color.Green500);
	}

	if (!Driver->IsDriverStarted())
	{
		this->Print("Service is not running, starting new...", D3DX9->Color.Orange400);
		if (!Driver->StartDriver())
		{
			this->Print("StartServiceA failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
			return;
		}
	}
	else
	{
		this->Print("Service is already running", D3DX9->Color.Green500);
	}

	Core->ProcessId = Utils->GetProcessId(L"League of Legends.exe");
	if (Core->ProcessId <= 0)
	{
		this->Print("Could not find game process", D3DX9->Color.Red600);
		return;
	}

	Core->hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, Core->ProcessId);
	if (Core->hProcess <= 0)
	{
		this->Print("OpenProcess failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
		return;
	}

	if (!Core->IsSectionProtected())
	{
		this->Print("Patch failed, please restart game. Contact admin if you can't fix this error.", D3DX9->Color.Red600);
		return;
	}

	Core->RestoreNtdll();

	void* pDllPath = VirtualAllocEx(Core->hProcess, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pDllPath <= 0)
	{
		this->Print("VirtualAllocEx failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
		return;
	}

	if (!WriteProcessMemory(Core->hProcess, pDllPath, Core->CorePath.c_str(), strlen(Core->CorePath.c_str()) + 1, 0))
	{
		VirtualFreeEx(Core->hProcess, pDllPath, 0, MEM_RELEASE);
		this->Print("WriteProcessMemory failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
		return;
	}

	HANDLE hThread = CreateRemoteThread(Core->hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pDllPath, 0, 0);
	if (hThread <= 0)
	{
		VirtualFreeEx(Core->hProcess, pDllPath, 0, MEM_RELEASE);
		this->Print("CreateRemoteThread failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
		return;
	}

	if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
	{
		VirtualFreeEx(Core->hProcess, pDllPath, 0, MEM_RELEASE);
		this->Print("WaitForSingleObject failed with code: " + Utils->int_to_hex(GetLastError()), D3DX9->Color.Red600);
		return;
	}

	VirtualFreeEx(Core->hProcess, pDllPath, 0, MEM_RELEASE);

	this->Print("Injected successfully.", D3DX9->Color.Green500);
	Sleep(1500);
	ExitProcess(0);
}