#pragma once

#include "../../WinMain.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_internal.h"

namespace ImGui_Ex
{
	void StyleColorMidnight(ImGuiStyle* dst = NULL);

	void StyleColorDarkGreen(ImGuiStyle* dst = NULL);

	void StyleColorDeepDark(ImGuiStyle* dst = NULL);

	void StyleColorDarkSlate(ImGuiStyle* dst = NULL);

	const ImWchar* GetGlyphRangesUnicode();

	const ImWchar* GetGlyphRangesAll();

	const ImWchar* GetGlyphRangesArialUni();

	const ImWchar* GetGlyphRangesUnifont();

	void AddSrollBarBorder();

	void AddWindowBorder();

	void TextWrappedColored(const ImVec4& col, const char* fmt, ...);

	void TextURL(const char* name_, const char* URL_);

	void TextColoredURL(const ImVec4& col, ImColor UnderlineCol, const char* name_, const char* URL_);

	void IconURL(ImFont* pIconFont, const char* name_, const char* URL_);

	void TextCenteredW(const char* text);

	void TextCenteredW(const ImVec4& col, const char* text);

	void TextCenteredH(const char* text);

	void TextCenteredH(const ImVec4& col, const char* text);

	void TextCenteredWH(const char* text);

	void TextCenteredWH(const ImVec4& col, const char* text);

	void TextBottom(const char* text);

	void TextBottom(const ImVec4& col, const char* text);

	void HelpMarker(const char* desc);

	void AddCircleImageFilled(ImTextureID user_texture_id, const ImVec2& centre, float radius, ImU32 col, int num_segments);

	bool IndentButton(const char* label, const ImVec2& size_arg, float indentSize);
};