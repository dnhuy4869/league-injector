#pragma once

#include "../WinMain.h"
#include "../PopupWindow/PopupWindow.h"
#include "../Dependencies/imgui_ex/imgui_ex.h"
#include "../Utilities/Utilities.h"

class Core
{
public:

	void ExitFailed(const char* log);

	bool IsImGuiCreated = false;
};