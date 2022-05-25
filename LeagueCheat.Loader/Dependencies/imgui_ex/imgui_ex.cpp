#include "./imgui_ex.h"

void ImGui_Ex::StyleColorMidnight(ImGuiStyle* dst)
{
	ImGuiStyle* Style = &ImGui::GetStyle();

	Style->ChildRounding = 0.0f;
	Style->FrameRounding = 0.0f;
	Style->PopupRounding = 0.0f;
	Style->ScrollbarRounding = 0.0f;
	Style->TabRounding = 0.0f;
	Style->GrabRounding = 0.0f;
	Style->WindowRounding = 0.0f;
	Style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	Style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	Style->ItemSpacing = ImVec2(8.0f, 4.0f);

	Style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	Style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	Style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	Style->Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	Style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	Style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	Style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
	Style->Colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.13f, 0.16f, 1.00f);
	Style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.13f, 0.16f, 1.00f);
	Style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.13f, 0.16f, 1.00f);
	Style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	Style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	Style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.19f, 0.17f, 0.21f, 1.00f);
	Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
	Style->Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.46f, 0.79f, 1.00f);
	Style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	Style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	Style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	Style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	Style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
	Style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	Style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	Style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
	Style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	Style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	Style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	Style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	Style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	Style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	Style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}

void ImGui_Ex::StyleColorDarkGreen(ImGuiStyle* dst)
{
	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;
	Style->ScrollbarRounding = 4.0f;
	Style->WindowTitleAlign = ImVec2(0.5f, 0.5f);

	Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	Colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	Colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
	Colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
	Colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	Colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	Colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
	Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	Colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	Colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	Colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void ImGui_Ex::StyleColorDeepDark(ImGuiStyle* dst)
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.93f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_Header] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	//colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	//colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	//style.WindowPadding = ImVec2(8.00f, 8.00f);
	//style.FramePadding = ImVec2(5.00f, 2.00f);
	//style.CellPadding = ImVec2(6.00f, 6.00f);
	//style.ItemSpacing = ImVec2(6.00f, 6.00f);
	//style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	//style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	//style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	//style.GrabMinSize = 10;
	//style.WindowBorderSize = 1;
	//style.ChildBorderSize = 1;
	//style.PopupBorderSize = 1;
	//style.FrameBorderSize = 1;
	//style.TabBorderSize = 1;
	//style.LogSliderDeadzone = 4;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	style.ScrollbarRounding = 9;
	style.TabRounding = 0;
	style.GrabRounding = 0;
	style.WindowRounding = 0;
	style.ChildRounding = 0;
	style.FrameRounding = 0;
	style.PopupRounding = 0;
}

void ImGui_Ex::StyleColorDarkSlate(ImGuiStyle* dst)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::StyleColorsDark();

	style->Alpha = 1.f;
	style->WindowRounding = 0.0f;
	style->ItemSpacing = ImVec2(8.0f, 4.0f);
	style->ScrollbarSize = 17.0f;
	style->ScrollbarRounding = 14.f;
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	//style->AntiAliasedLines = false;
	//style->AntiAliasedFill = false;
	//style->AntiAliasedLinesUseTex = false;

	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = ImColor(226, 232, 240);
	colors[ImGuiCol_WindowBg] = ImColor(15, 23, 42);
	colors[ImGuiCol_ChildBg] = ImColor(23, 33, 52);
	colors[ImGuiCol_Border] = ImVec4(30, 41, 59, 0);
	colors[ImGuiCol_FrameBg] = ImColor(41, 51, 65);
	colors[ImGuiCol_FrameBgHovered] = ImColor(55, 65, 81);
	colors[ImGuiCol_FrameBgActive] = ImColor(75, 85, 99);
	colors[ImGuiCol_Header] = ImColor(31, 41, 55);
	colors[ImGuiCol_HeaderHovered] = ImColor(55, 65, 81);
	colors[ImGuiCol_HeaderActive] = ImColor(75, 85, 99);
	colors[ImGuiCol_TitleBg] = ImColor(31, 41, 55);
	colors[ImGuiCol_TitleBgActive] = ImColor(55, 65, 81);
	colors[ImGuiCol_TitleBgCollapsed] = ImColor(75, 85, 99);
	colors[ImGuiCol_PopupBg] = ImColor(31, 41, 55);
	colors[ImGuiCol_Button] = ImColor(109, 40, 217);
	colors[ImGuiCol_ButtonHovered] = ImColor(124, 58, 237);
	colors[ImGuiCol_ButtonActive] = ImColor(139, 92, 246);
	colors[ImGuiCol_ScrollbarBg] = ImColor(31, 41, 55);
	colors[ImGuiCol_ScrollbarGrab] = ImColor(110, 122, 200);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(110, 122, 200, 153);
	colors[ImGuiCol_ScrollbarGrabActive] = ImColor(110, 122, 200, 153);
	colors[ImGuiCol_SliderGrab] = ImColor(203, 213, 225);
	colors[ImGuiCol_SliderGrabActive] = ImColor(226, 232, 240);
	colors[ImGuiCol_CheckMark] = ImColor(203, 213, 225);
}

const ImWchar* ImGui_Ex::GetGlyphRangesUnicode()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x007F, // Basic Latin
		0x00A0, 0x00FF, // Latin-1 Supplement
		0x0100, 0x017F, // Latin Extended-A
		0x0180, 0x024F, // Latin Extended-B 
		0x0250, 0x02AF, // IPA Extensions
		0x02B0, 0x02FF, // Spacing Modifier Letters
		0x0300, 0x036F, // Combining Diacritical Marks
		0x0370, 0x03FF, // Greek and Coptic
		0x0400, 0x04FF, // Cyrillic
		0x0500, 0x052F, // Cyrillic Supplementary
		0x0530, 0x058F, // Armenian
		0x0590, 0x05FF, // Hebrew
		0x0600, 0x06FF, // Arabic
		0x0700, 0x074F, // Syriac
		0x0780, 0x07BF, // Thaana
		0x0900, 0x097F, // Devanagari
		0x0980, 0x09FF, // Bengali
		0x0A00, 0x0A7F, // Gurmukhi
		0x0A80, 0x0AFF, // Gujarati
		0x0B00, 0x0B7F, // Oriya
		0x0B80, 0x0BFF, // Tamil
		0x0C00, 0x0C7F, // Telugu
		0x0C80, 0x0CFF, // Kannada
		0x0D00, 0x0D7F, // Malayalam
		0x0D80, 0x0DFF, // Sinhala
		0x0E00, 0x0E7F, // Thai
		0x0E80, 0x0EFF, // Lao
		0x0F00, 0x0FFF, // Tibetan
		0x1000, 0x109F, // Myanmar
		0x10A0, 0x10FF, // Georgian
		0x1100, 0x11FF, // Hangul Jamo
		0x1200, 0x137F, // Ethiopic
		0x13A0, 0x13FF, // Cherokee
		0x1400, 0x167F, // Unified Canadian Aboriginal Syllabics
		0x1680, 0x169F, // Ogham
		0x16A0, 0x16FF, // Runic
		0x1700, 0x171F, // Tagalog
		0x1720, 0x173F, // Hanunoo
		0x1740, 0x175F, // Buhid
		0x1760, 0x177F, // Tagbanwa
		0x1780, 0x17FF, // Khmer
		0x1800, 0x18AF, // Mongolian
		0x1900, 0x194F, // Limbu
		0x1950, 0x197F, // Tai Le
		0x19E0, 0x19FF, // Khmer Symbols
		0x1D00, 0x1D7F, // Phonetic Extensions
		0x1E00, 0x1EFF, // Latin Extended Additional
		0x1F00, 0x1FFF, // Greek Extended
		0x2000, 0x206F, // General Punctuation
		0x2070, 0x209F, // Superscripts and Subscripts
		0x20A0, 0x20CF, // Currency Symbols
		0x20D0, 0x20FF, // Combining Diacritical Marks for Symbols
		0x2100, 0x214F, // Letterlike Symbols
		0x2150, 0x218F, // Number Forms
		0x2190, 0x21FF, // Arrows
		0x2200, 0x22FF, // Mathematical Operators
		0x2300, 0x23FF, // Miscellaneous Technical
		0x2400, 0x243F, // Control Pictures
		0x2440, 0x245F, // Optical Character Recognition
		0x2460, 0x24FF, // Enclosed Alphanumerics
		0x2500, 0x257F, // Box Drawing
		0x2580, 0x259F, // Block Elements
		0x25A0, 0x25FF, // Geometric Shapes
		0x2600, 0x26FF, // Miscellaneous Symbols
		0x2700, 0x27BF, // Dingbats
		0x27C0, 0x27EF, // Miscellaneous Mathematical Symbols - A
		0x27F0, 0x27FF, // Supplemental Arrows - A
		0x2800, 0x28FF, // Braille Patterns
		0x2900, 0x297F, // Supplemental Arrows - B
		0x2980, 0x29FF, // Miscellaneous Mathematical Symbols - B
		0x2A00, 0x2AFF, // Supplemental Mathematical Operators
		0x2B00, 0x2BFF, // Miscellaneous Symbols and Arrows
		0x2E80, 0x2EFF, // CJK Radicals Supplement
		0x2F00, 0x2FDF, // Kangxi Radicals
		0x2FF0, 0x2FFF, // Ideographic Description Characters
		0x3000, 0x303F, // CJK Symbols and Punctuation
		0x3040, 0x309F, // Hiragana
		0x30A0, 0x30FF, // Katakana
		0x3100, 0x312F, // Bopomofo
		0x3130, 0x318F, // Hangul Compatibility Jamo
		0x3190, 0x319F, // Kanbun
		0x31A0, 0x31BF, // Bopomofo Extended
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0x3200, 0x32FF, // Enclosed CJK Letters and Months
		0x3300, 0x33FF, // CJK Compatibility
		0x3400, 0x4DBF, // CJK Unified Ideographs Extension A
		0x4DC0, 0x4DFF, // Yijing Hexagram Symbols
		0x4E00, 0x9FFF, // CJK Unified Ideographs
		0xA000, 0xA48F, // Yi Syllables
		0xA490, 0xA4CF, // Yi Radicals
		0xAC00, 0xD7AF, // Hangul Syllables
		0xD800, 0xDB7F, // High Surrogates
		0xDB80, 0xDBFF, // High Private Use Surrogates
		0xDC00, 0xDFFF, // Low Surrogates
		0xE000, 0xF8FF, // Private Use Area
		0xF900, 0xFAFF, // CJK Compatibility Ideographs
		0xFB00, 0xFB4F, // Alphabetic Presentation Forms
		0xFB50, 0xFDFF, // Arabic Presentation Forms - A
		0xFE00, 0xFE0F, // Variation Selectors
		0xFE20, 0xFE2F, // Combining Half Marks
		0xFE30, 0xFE4F, // CJK Compatibility Forms
		0xFE50, 0xFE6F, // Small Form Variants
		0xFE70, 0xFEFF, // Arabic Presentation Forms - B
		0xFF00, 0xFFEF, // Halfwidthand Fullwidth Forms
		0xFFF0, 0xFFFF, // Specials
		0x10000, 0x1007F, // Linear B Syllabary
		0x10080, 0x100FF, // Linear B Ideograms
		0x10100, 0x1013F, // Aegean Numbers
		0x10300, 0x1032F, // Old Italic
		0x10330, 0x1034F, // Gothic
		0x10380, 0x1039F, // Ugaritic
		0x10400, 0x1044F, // Deseret
		0x10450, 0x1047F, // Shavian
		0x10480, 0x104AF, // Osmanya
		0x10800, 0x1083F, // Cypriot Syllabary
		0x1D000, 0x1D0FF, // Byzantine Musical Symbols
		0x1D100, 0x1D1FF, // Musical Symbols
		0x1D300, 0x1D35F, // Tai Xuan Jing Symbols
		0x1D400, 0x1D7FF, // Mathematical Alphanumeric Symbols
		0x20000, 0x2A6DF, // CJK Unified Ideographs Extension B
		0x2F800, 0x2FA1F, // CJK Compatibility Ideographs Supplement
		0xE0000, 0xE007F, // Tags
		0
	};

	return &ranges[0];
}

const ImWchar* ImGui_Ex::GetGlyphRangesAll()
{
	static const ImWchar ranges[] =
	{
		0x0000, 0xFFFF, // Total Characters in BMP
		0x10000, 0x1FFFF, // Total Characters in SMP
		0x20000, 0x2FFFF, // Total Characters in SIP 
		0xE0000, 0xEFFFF, // Total Characters in SSP
		0
	};

	return &ranges[0];
}

const ImWchar* ImGui_Ex::GetGlyphRangesArialUni()
{
	static const ImWchar ranges[] =
	{
		0x0020, 0x007E, // Basic Latin
		0x007F, 0x007F, // Delete Character
		0x00A0, 0x00FF, // Latin-1 Supplement
		0x0100, 0x017F, // Latin Extended-A
		0x0180, 0x024F, // Latin Extended-B
		0x0250, 0x02AF, // IPA Extensions
		0x02B0, 0x02FF, // Spacing Modifier Letters
		0x0300, 0x036F, // Combining Diacritical Marks
		0x0370, 0x03FF, // Greek and Coptic
		0x0400, 0x04FF, // Cyrillic
		0x0530, 0x058F, // Armenian
		0x0590, 0x05FF, // Hebrew
		0x0600, 0x06FF, // Arabic
		0x0900, 0x097F, // Devanagari
		0x0980, 0x09FF, // Bengali
		0x0A00, 0x0A7F, // Gurmukhi
		0x0A80, 0x0AFF, // Gujarati
		0x0B00, 0x0B7F, // Oriya
		0x0B80, 0x0BFF, // Tamil
		0x0C00, 0x0C7F, // Telugu
		0x0C80, 0x0CFF, // Kannada
		0x0D00, 0x0D7F, // Malayalam
		0x0E00, 0x0E7F, // Thai
		0x0E80, 0x0EFF, // Lao
		0x0F00, 0x0FFF, // Tibetan
		0x10A0, 0x10FF, // Georgian
		0x1100, 0x115F, // Hangul Jamo: Choseong 
		0x1160, 0x11A7, // Hangul Jamo: Jungseong
		0x11A8, 0x11FF, // Hangul Jamo: Jongseong
		0x1E00, 0x1EFF, // Latin Extended Additional 
		0x1F00, 0x1FFF, // Greek Extended
		0x2000, 0x206F, // General Punctuation
		0x2070, 0x209F, // Superscripts and Subscripts
		0x20A0, 0x20CF, // Currency Symbols
		0x20D0, 0x20FF, // Combining Diacritical Marks for Symbols
		0x2100, 0x214F, // Letterlike Symbols
		0x2150, 0x218F, // Number Forms
		0x2190, 0x21FF, // Arrows
		0x2200, 0x22FF, // Mathematical Operators
		0x2300, 0x23FF, // Miscellaneous Technical
		0x2400, 0x243F, // Control Pictures
		0x2440, 0x245F, // Optical Character Recognition
		0x2460, 0x24FF, // Enclosed Alphanumerics
		0x2500, 0x257F, // Box Drawing
		0x2580, 0x259F, // Block Elements
		0x25A0, 0x25FF, // Geometric Shapes
		0x2600, 0x267F, // Miscellaneous Symbols
		0x2700, 0x27BF, // Dingbats
		0x3000, 0x303F, // CJK Symbols and Punctuation
		0x3040, 0x309F, // Hiragana
		0x30A0, 0x30FF, // Katakana
		0x3100, 0x312F, // Bopomofo
		0x3130, 0x318F, // Hangul Compatibility Jamo
		0x3190, 0x319F, // Kanbun
		0x3200, 0x32FF, // Enclosed CJK Letters and Months
		0x3300, 0x33FF, // CJK Compatibility
		0x4E00, 0x9FFF, // CJK Unified Ideographs (Han Unification)
		0xA490, 0xA4AF, // Yi Radicals
		0xAC00, 0xD7AF, // Hangul Syllables
		0xE000, 0xF8FF, // Private Use Area
		0xF900 ,0xFAFF, // CJK Compatibility Ideographs
		0xFB00, 0xFB4F, // Alphabetic Presentation Forms (Latin Lig + Armenian Lig + Hebrew Lig)
		0xFB00, 0xFB06, // Latin Ligatures
		0xFB13, 0xFB17, // Armenian Ligatures
		0xFB1D, 0xFB4F, // Hebrew Ligatures / Pointed Letters 
		0xFB50, 0xFDFF, // Arabic Presentation Forms-A
		0xFE20, 0xFE2F, // Combining Half Marks
		0xFE30, 0xFE4F, // CJK Compatibility Forms
		0xFE50, 0xFE6F, // Small Form Variants
		0xFE70, 0xFEFF, // Arabic Presentation Forms-B
		0xFF00, 0xFFEF, // Halfwidth and Fullwidth Forms
		0xFF01, 0xFF5E, // Latin Full Width Forms
		0xFF61, 0xFF9F, // KataKana Half Width Forms
		0xFFA0, 0xFFDC, // Hangul Jamo Half Width Forms
		0xFFF0, 0xFFFF, // Specials
		0
	};

	return &ranges[0];
}

const ImWchar* ImGui_Ex::GetGlyphRangesUnifont()
{
	static const ImWchar ranges[] =
	{
		//0x0000, 0x001F, // C0 Control Character
		0x0020, 0x007E, // Basic Latin
		0x007F, 0x007F, // Delete Character
		0x0080, 0x009F, // C1 Control Character
		0x00A0, 0x00FF, // Latin - 1 Supplement
		0x0100, 0x017F, // Latin Extended - A
		0x0180, 0x024F, // Latin Extended - B
		0x0250, 0x02AF, // IPA Extensions
		0x02B0, 0x02FF, // Spacing Modifier Letters
		0x0300, 0x036F, // Combining Diacritical Marks
		0x0370, 0x03FF, // Greekand Coptic
		0x0400, 0x04FF, // Cyrillic
		0x0500, 0x052F, // Cyrillic Supplement
		0x0530, 0x058F, // Armenian
		0x0590, 0x05FF, // Hebrew
		0x0600, 0x06FF, // Arabic
		0x0700, 0x074F, // Syriac
		0x0750, 0x077F, // Arabic Supplement
		0x0780, 0x07BF, // Thaana
		0x07C0, 0x07FF, // NKo
		0x0800, 0x083F, // Samaritan
		0x0840, 0x085F, // Mandaic
		0x08A0, 0x08FF, // Arabic Extended - A
		0x0900, 0x097F, // Devanagari
		0x0980, 0x09FF, // Bengali
		0x0A00, 0x0A7F, // Gurmukhi
		0x0A80, 0x0AFF, // Gujarati
		0x0B00, 0x0B7F, // Oriya
		0x0B80, 0x0BFF, // Tamil
		0x0C00, 0x0C7F, // Telugu
		0x0C80, 0x0CFF, // Kannada
		0x0D00, 0x0D7F, // Malayalam
		0x0D80, 0x0DFF, // Sinhala
		0x0E00, 0x0E7F, // Thai
		0x0E80, 0x0EFF, // Lao
		0x0F00, 0x0FFF, // Tibetan
		0x1000, 0x109F, // Myanmar(Burmese)
		0x10A0, 0x10FF, // Georgian
		0x1100, 0x115F, // Hangul Jamo : Choseong
		0x1160, 0x11A7, // Hangul Jamo : Jungseong
		0x11A8, 0x11FF, // Hangul Jamo : Jongseong
		0x1200, 0x137F, // Ethiopic(Ge'ez)
		0x1380, 0x139F, // Ethiopic Supplement(Ge'ez)
		0x13A0, 0x13FF, // Cherokee
		0x1400, 0x167F, // Unified Canadian Aboriginal Syllabics
		0x1680, 0x169F, // Ogham
		0x16A0, 0x16FF, // Runic
		0x1700, 0x171F, // Tagalog(Baybayin)
		0x1720, 0x173F, // Hanunoo(Hanunó'o)
		0x1740, 0x175F, // Buhid
		0x1760, 0x177F, // Tagbanwa
		0x1780, 0x17FF, // Khmer
		0x1800, 0x18AF, // Mongolian
		0x18B0, 0x18FF, // Unified Canadian Aboriginal Syllabics Extended
		0x1900, 0x194F, // Limbu
		0x1950, 0x197F, // Tai Le
		0x1980, 0x19DF, // New Tai Lue(Tai Lü)
		0x19E0, 0x19FF, // Khmer Symbols
		0x1A00, 0x1A1F, // Buginese
		0x1A20, 0x1AAF, // Tai Tham
		0x1B00, 0x1B7F, // Balinese
		0x1B80, 0x1BBF, // Sundanese
		0x1BC0, 0x1BFF, // Batak
		0x1C00, 0x1C4F, // Lepcha
		0x1C50, 0x1C7F, // Ol Chiki
		0x1CC0, 0x1CCF, // Sundanese Supplement
		0x1CD0, 0x1CFF, // Vedic Extensions
		0x1D00, 0x1D7F, // Phonetic Extensions
		0x1D80, 0x1DBF, // Phonetic Extensions Supplement
		0x1DC0, 0x1DFF, // Combining Diacritical Marks Supplement
		0x1E00, 0x1EFF, // Latin Extended Additional
		0x1F00, 0x1FFF, // Greek Extended
		0x2000, 0x206F, // General Punctuation
		0x2070, 0x209F, // Superscriptsand Subscripts
		0x20A0, 0x20CF, // Currency Symbols
		0x20D0, 0x20FF, // Combining Diacritical Marks for Symbols
		0x2100, 0x214F, // Letterlike Symbols
		0x2150, 0x218F, // Number Forms
		0x2190, 0x21FF, // Arrows
		0x2200, 0x22FF, // Mathematical Operators
		0x2300, 0x23FF, // Miscellaneous Technical
		0x2400, 0x243F, // Control Pictures
		0x2440, 0x245F, // Optical Character Recognition
		0x2460, 0x24FF, // Enclosed Alphanumerics
		0x2500, 0x257F, // Box Drawing
		0x2580, 0x259F, // Block Elements
		0x25A0, 0x25FF, // Geometric Shapes
		0x2600, 0x267F, // Miscellaneous Symbols
		0x2700, 0x27BF, // Dingbats(Zapf Dingbats)
		0x27C0, 0x27EF, // Miscellaneous Mathematical Symbols - A
		0x27F0, 0x27FF, // Supplemental Arrows - A
		0x2800, 0x28FF, // Braille Patterns
		0x2900, 0x297F, // Supplemental Arrows - B
		0x2980, 0x29FF, // Miscellaneous Mathematical Symbols - B
		0x2A00, 0x2AFF, // Supplemental Mathematical Operators
		0x2B00, 0x2BFF, // Miscellaneous Symbolsand Arrows
		0x2C00, 0x2C5F, // Glagolitic
		0x2C60, 0x2C7F, // Latin Extended - C
		0x2C80, 0x2CFF, // Coptic
		0x2D00, 0x2D2F, // Georgian Supplement
		0x2D30, 0x2D7F, // Tifinagh
		0x2D80, 0x2DDF, // Ethiopic Extended
		0x2DE0, 0x2DFF, // Cyrillic Extended - A
		0x2E00, 0x2E7F, // Supplemental Punctuation
		0x2E80, 0x2EFF, // CJK Radicals Supplement
		0x2F00, 0x2FDF, // Kangxi Radicals
		0x2FF0, 0x2FFF, // Ideographic Description Characters
		0x3000, 0x303F, // CJK Symbolsand Punctuation
		0x3040, 0x309F, // Hiragana
		0x30A0, 0x30FF, // Katakana
		0x3100, 0x312F, // Bopomofo
		0x3130, 0x318F, // Hangul Compatibility Jamo
		0x3190, 0x319F, // Kanbun
		0x31A0, 0x31BF, // Bopomofo Extended
		0x31C0, 0x31EF, // CJK Strokes
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0x3200, 0x32FF, // Enclosed CJK Lettersand Months
		0x3300, 0x33FF, // CJK Compatibility
		0x3400, 0x4DBF, // CJK Unified Ideographs Extension A
		0x4DC0, 0x4DFF, // Yijing Hexagram Symbols
		0x4E00, 0x9FFF, // CJK Unified Ideographs(Han Unification)
		0xA000, 0xA3FF, // Yi Syllables
		0xA490, 0xA4AF, // Yi Radicals
		0xA4D0, 0xA4FF, // Lisu(Fraser alphabet)
		0xA500, 0xA63F, // Vai
		0xA640, 0xA69F, // Cyrillic Extended - B
		0xA6A0, 0xA6FF, // Bamum
		0xA700, 0xA71F, // Modifier Tone Letters
		0xA720, 0xA7FF, // Latin Extended - D
		0xA800, 0xA82F, // Syloti Nagri
		0xA830, 0xA83F, // Common Indic Number Forms
		0xA840, 0xA87F, // Phags - pa
		0xA880, 0xA8DF, // Saurashtra
		0xA8E0, 0xA8FF, // Devanagari Extended
		0xA900, 0xA92F, // Kayah Li
		0xA930, 0xA95F, // Rejang
		0xA960, 0xA97F, // Hangul Jamo Extended - A
		0xA980, 0xA9DF, // Javanese
		0xAA00, 0xAA5F, // Cham
		0xAA60, 0xAA7F, // Myanmar Extended - A
		0xAA80, 0xAADF, // Tai Viet
		0xAAE0, 0xAAFF, // Meetei Mayek Extensions
		0xAB00, 0xAB2F, // Ethiopic Extended - A
		0xABC0, 0xABF9, // Meetei Mayek
		0xAC00, 0xD7AF, // Hangul Syllables
		0xD7B0, 0xD7FF, // Hangul Jamo Extended - B
		0xE000, 0xF8FF, // Private Use Area
		0xF900, 0xFAFF, // CJK Compatibility Ideographs
		0xFB00, 0xFB4F, // Alphabetic Presentation Forms(Latin Lig + Armenian Lig + Hebrew Lig)
		0xFB00, 0xFB06, // Latin Ligatures
		0xFB13, 0xFB17, // Armenian Ligatures
		0xFB1D, 0xFB4F, // Hebrew Ligatures / Pointed Letters
		0xFB50, 0xFDFF, // Arabic Presentation Forms - A
		0xFE00, 0xFE0F, // Variation Selectors
		0xFE10, 0xFE1F, // Vertical Forms
		0xFE20, 0xFE2F, // Combining Half Marks
		0xFE30, 0xFE4F, // CJK Compatibility Forms
		0xFE50, 0xFE6F, // Small Form Variants
		0xFE70, 0xFEFF, // Arabic Presentation Forms - B
		0xFEFF, 0xFEFF, // Byte Order Mark
		0xFF00, 0xFFEF, // Halfwidthand Fullwidth Forms
		0xFF01, 0xFF5E, // Latin Full Width Forms
		0xFF61, 0xFF9F, // KataKana Half Width Forms
		0xFFA0, 0xFFDC, // Hangul Jamo Half Width Forms
		0xFFF0, 0xFFFF, // Specials
		0
	};

	return &ranges[0];
}

void ImGui_Ex::AddSrollBarBorder()
{
	ImGuiWindow* Window = ImGui::GetCurrentWindow();
	if (Window->ScrollbarX || Window->ScrollbarY)
	{
		ImGui::PushClipRect(Window->OuterRectClipped.Min, Window->OuterRectClipped.Max, false);

		if (Window->ScrollbarX)
		{
			ImRect Rect = ImGui::GetWindowScrollbarRect(Window, ImGuiAxis_X);
			Window->DrawList->AddRect(Rect.Min, Rect.Max, IM_COL32(110, 110, 128, 128));
		}
		if (Window->ScrollbarY)
		{
			ImRect Rect = ImGui::GetWindowScrollbarRect(Window, ImGuiAxis_Y);
			Window->DrawList->AddRect(Rect.Min, Rect.Max, IM_COL32(110, 110, 128, 128));
		}

		ImGui::PopClipRect();
	}
}

void ImGui_Ex::AddWindowBorder()
{
	ImGuiWindow* Window = ImGui::GetCurrentWindow();
	Window->DrawList->AddRect(
		ImVec2(Window->Pos.x + 3.0f, Window->Pos.y + 0.5f),
		ImVec2(Window->Pos.x + Window->Size.x - 3.0f, Window->Pos.y + Window->Size.y - 0.5f),
		ImColor(148, 163, 184),
		0,
		0,
		0.5f
	);
}

void TextWrappedColoredV(const ImVec4& col, const char* fmt, va_list args)
{
	ImGui::PushStyleColor(ImGuiCol_Text, col);
	ImGuiContext& g = *GImGui;
	bool need_backup = (g.CurrentWindow->DC.TextWrapPos < 0.0f);
	if (need_backup)
		ImGui::PushTextWrapPos(0.0f);
	if (fmt[0] == '%' && fmt[1] == 's' && fmt[2] == 0)
		ImGui::TextEx(va_arg(args, const char*), NULL, ImGuiTextFlags_NoWidthForLargeClippedText);
	else
		ImGui::TextV(fmt, args);
	if (need_backup)
		ImGui::PopTextWrapPos();
	ImGui::PopStyleColor();
}

void ImGui_Ex::TextWrappedColored(const ImVec4& col, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	TextWrappedColoredV(col, fmt, args);
	va_end(args);
}

void AddUnderLine(ImColor col_)
{
	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();
	min.y = max.y;
	ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
}

void ImGui_Ex::TextURL(const char* name_, const char* URL_)
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
	ImGui::Text(name_);
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered())
	{
		if (ImGui::IsMouseClicked(0))
		{
			ShellExecuteA(NULL, "open", URL_, NULL, NULL, SW_HIDE);
		}
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
		ImGui::SetTooltip("\xef\x83\x81" "  Open in browser\n%s", URL_);
	}
	else
	{
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_Button]);
	}
}

void ImGui_Ex::TextColoredURL(const ImVec4& col, ImColor UnderlineCol, const char* name_, const char* URL_)
{
	ImGui::PushStyleColor(ImGuiCol_Text, col);
	ImGui::Text(name_);
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered())
	{
		if (ImGui::IsMouseClicked(0))
		{
			ShellExecuteA(NULL, "open", URL_, NULL, NULL, SW_HIDE);
		}
		AddUnderLine(UnderlineCol);
		ImGui::SetTooltip("\xef\x83\x81" "  Open in browser:\n%s", URL_);
	}
	else
	{
		AddUnderLine(UnderlineCol);
	}
}

void ImGui_Ex::IconURL(ImFont* pIconFont, const char* name_, const char* URL_)
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushFont(pIconFont);
	ImGui::Text(name_);
	ImGui::PopFont();
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered())
	{
		if (ImGui::IsMouseClicked(0))
		{
			ShellExecuteA(NULL, "open", URL_, NULL, NULL, SW_HIDE);
		}
	}
}

void ImGui_Ex::TextCenteredW(const char* text)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text);
}

void ImGui_Ex::TextCenteredW(const ImVec4& col, const char* text)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::TextColored(col, text);
}

void ImGui_Ex::TextCenteredH(const char* text)
{
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
	ImGui::Text(text);
}

void ImGui_Ex::TextCenteredH(const ImVec4& col, const char* text)
{
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
	ImGui::TextColored(col, text);
}

void ImGui_Ex::TextCenteredWH(const char* text)
{
	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize(text).x;
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
	ImGui::Text(text);
}

void ImGui_Ex::TextCenteredWH(const ImVec4& col, const char* text)
{
	float windowWidth = ImGui::GetWindowSize().x;
	float textWidth = ImGui::CalcTextSize(text).x;
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
	ImGui::TextColored(col, text);
}

void ImGui_Ex::TextBottom(const char* text)
{
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosY(windowHeight - textHeight);
	ImGui::Text(text);
}

void ImGui_Ex::TextBottom(const ImVec4& col, const char* text)
{
	float windowHeight = ImGui::GetWindowSize().y;
	float textHeight = ImGui::CalcTextSize(text).y;

	ImGui::SetCursorPosY(windowHeight - textHeight);
	ImGui::TextColored(col, text);
}

void ImGui_Ex::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImGui_Ex::AddCircleImageFilled(ImTextureID user_texture_id, const ImVec2& centre, float radius, ImU32 col, int num_segments)
{
	auto window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	window->DrawList->PathClear();

	if ((col & IM_COL32_A_MASK) == 0 || num_segments <= 2)
		return;

	const bool push_texture_id = window->DrawList->_TextureIdStack.empty() || user_texture_id != window->DrawList->_TextureIdStack.back();
	if (push_texture_id)
		window->DrawList->PushTextureID(user_texture_id);

	int vert_start_idx = window->DrawList->VtxBuffer.Size;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	window->DrawList->PathArcTo(centre, radius, 0.0f, a_max, num_segments - 1);
	window->DrawList->PathFillConvex(col);
	int vert_end_idx = window->DrawList->VtxBuffer.Size;

	ImGui::ShadeVertsLinearUV(window->DrawList, vert_start_idx, vert_end_idx, ImVec2(centre.x - radius, centre.y - radius), ImVec2(centre.x + radius, centre.y + radius), ImVec2(0, 0), ImVec2(1, 1), true);

	if (push_texture_id)
		window->DrawList->PopTextureID();
}

bool ImGui_Ex::IndentButton(const char* label, const ImVec2& size_arg, float indentSize)
{
	ImGuiButtonFlags flags = ImGuiButtonFlags_None;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

	// Render
	const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	ImGui::RenderNavHighlight(bb, id);
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

	if (g.LogEnabled)
		ImGui::LogSetNextTextDecoration("[", "]");
	ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x + indentSize, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label, NULL, &label_size, style.ButtonTextAlign, &bb);

	// Automatically close popups
	//if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
	//    CloseCurrentPopup();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
	return pressed;
}