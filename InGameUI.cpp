﻿#include "stdafx.h"
#include "d3d9.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_internal.h"

void createImGui(LPDIRECT3DDEVICE9 pD3DDevice, D3DPRESENT_PARAMETERS* pParams)
{
	ImGui_ImplDX9_Init(pD3DDevice);
	ImGui::GetIO().DisplaySize = ImVec2((float)pParams->BackBufferWidth, (float)pParams->BackBufferHeight);
}

void lostImGui(LPDIRECT3DDEVICE9 pD3DDevice, D3DPRESENT_PARAMETERS* pParams)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui::GetIO().DisplaySize = ImVec2((float)pParams->BackBufferWidth, (float)pParams->BackBufferHeight);
}

void resetImGui(LPDIRECT3DDEVICE9 pD3DDevice, D3DPRESENT_PARAMETERS* pParams)
{
	ImGui_ImplDX9_CreateDeviceObjects();
	ImGui::GetIO().DisplaySize = ImVec2((float)pParams->BackBufferWidth, (float)(pParams->BackBufferHeight));
}

bool inGameUIEnabled = false;
WPARAM inGameUIHotkey;
std::vector<void(*)()> callbacks;
void drawImGui(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (!inGameUIEnabled)
		return;

	ImGui_ImplDX9_NewFrame();

	ImGui::SetNextWindowSize(ImVec2(450, 600), ImGuiSetCond_Once);
	ImGui::Begin("DDDAFix", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	for (size_t i = 0; i < callbacks.size(); i++)
	{
		ImGui::PushID(i);
		callbacks[i]();
		ImGui::PopID();
	}
	ImGui::End();

	ImGui::Render();
}

void Hooks::InGameUI()
{
	inGameUIHotkey = config.getUInt("hotkeys", "keyUI", VK_F12) & 0xFF;
	D3D9Add(createImGui, lostImGui, resetImGui, drawImGui);
}

void Hooks::InGameUIAdd(void(*callback)()) { callbacks.push_back(callback); }
LRESULT Hooks::InGameUIEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN && (HIWORD(lParam) & KF_REPEAT) == 0 && wParam == inGameUIHotkey)
		inGameUIEnabled = !inGameUIEnabled;
	return inGameUIEnabled ? ImGui_ImplDX9_WndProcHandler(hwnd, msg, wParam, lParam) : 0;
}

namespace ImGui
{
	bool InputFloatN(const char* label, float* v, int count, float item_width, float min, float max, int precision)
	{
		if (item_width > 0.0f)
			PushItemWidth(item_width * count);
		bool changed = InputFloatN(label, v, count, precision, 0);
		if (item_width > 0.0f)
			PopItemWidth();
		if (changed)
			for (int i = 0; i < count; i++)
			{
				if (v[i] < min)
					v[i] = min;
				if (v[i] > max)
					v[i] = max;
			}
		return changed;
	}

	bool InputFloatEx(const char* label, float* v, float step, float min, float max, int precision)
	{
		if (!InputFloat(label, v, step, 0.0f, precision, 0))
			return false;
		if (*v < min)
			*v = min;
		if (*v > max)
			*v = max;
		return true;
	}
}