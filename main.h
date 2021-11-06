#pragma once
#pragma warning(disable:4244)//игнорим потери при преобразовании типов
#pragma warning(disable:4267)//size_t в BYTE
#pragma warning(disable:4723)//деление на 0
#pragma warning(disable:4409)//большой размер
#pragma warning(disable:4552)//не использованный результат
#pragma warning(disable:4293)//большое битовое смещение
#pragma warning(disable:4724)//деление на 0
#pragma warning(disable:4804)//небезопасное использование типа "bool" в операции/This function or variable may be unsafe
#pragma comment(lib, "Winmm.lib")
#include "..\DirectX\d3d9.h"
#define DIRECTINPUT_VERSION 0x0800
#include <Windows.h>
#include <string>
#include <dinput.h>
#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#include <fstream>

#include "SAMPFUNCS_API.h"
#include "game_api.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx9.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_custom_funcs.h"

#include "HookRakNet.h"
#include "Present.h"
#include "Struct.h"
#include "ImGuiWindow.h"
#include "stuff.h"

#include "CollisionFunction.h"
#include "CollisionHook.h"


extern SAMPFUNCS *SF;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
