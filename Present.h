#pragma once
#include "main.h"

bool __stdcall Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters);

bool __stdcall WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam);