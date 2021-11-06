#include "Present.h"

bool FullScreen = false;
WINDOWPLACEMENT wpc;

double length(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void RenderBondage(void) {
	char buf[255];
	SF->getRender()->DrawLine(SF->getRender()->getPresentationParameters()->BackBufferWidth - 1400, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, SF->getRender()->getPresentationParameters()->BackBufferWidth - 1, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, 1, D3DCOLOR_XRGB(128, 128, 128)); 
	if (ImGuiWindow->GodMode) {
		pFont->Print("<GodMode>", D3DCOLOR_XRGB(255, 20, 147), SF->getRender()->getPresentationParameters()->BackBufferWidth - 1350, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
	}
	else {
		pFont->Print("{FF1493}<{808080}GodMode{FF1493}>", -1, SF->getRender()->getPresentationParameters()->BackBufferWidth - 1350, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
	}

	if (ImGuiWindow->AntiAFK) {
		pFont->Print("<AntiAFK>", D3DCOLOR_XRGB(255, 20, 147), SF->getRender()->getPresentationParameters()->BackBufferWidth - 1225, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
	}
	else {
		pFont->Print("{FF1493}<{808080}AntiAFK{FF1493}>", -1, SF->getRender()->getPresentationParameters()->BackBufferWidth - 1225, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
	}
	sprintf_s(buf, "{FF1493}%.2f   %.2f   %.2f", SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3], SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 1], SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3 + 2]);
	pFont->Print(buf, -1, SF->getRender()->getPresentationParameters()->BackBufferWidth - 750, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
	pFont->Print("{FF1493}GsH.{808080}clan", -1, SF->getRender()->getPresentationParameters()->BackBufferWidth - 150, SF->getRender()->getPresentationParameters()->BackBufferHeight - 20, false);
}

bool __stdcall Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion){
	if (SUCCEEDED(SF->getRender()->CanDraw()))
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (!ImGuiWindow->activew) {
			ImGuiWindow->ImGuiDrawMenu = false;
			SF->getSAMP()->getMisc()->ToggleCursor(false);
			ImGuiWindow->activew = true;
		}
		if (ImGuiWindow->ImGuiDrawMenu) 
			ImGuiDraw();
	
		if (ImGuiWindow->LogRPC) {
			char buf[255];
			sprintf_s(buf, "Outcoming RPC:%s \nIncoming RPC:%s", CState->LoggerOutcomingRPC, CState->LoggerIncomingRPC);
			pFont->Print(buf, -1, SF->getRender()->getPresentationParameters()->BackBufferWidth / 2, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2, false);
		}

		if(ImGuiWindow->SyncLogger)
			pFont->Print(ImGuiWindow->SyncAllLoggerPlayer, -1, SF->getRender()->getPresentationParameters()->BackBufferWidth / 2, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2, false);

		if (ImGuiWindow->Crosspiece) {
			SF->getRender()->DrawLine(SF->getRender()->getPresentationParameters()->BackBufferWidth / 2 + 38, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2 - 90, SF->getRender()->getPresentationParameters()->BackBufferWidth / 2 + 38, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2 - 70, 1, -1);
			SF->getRender()->DrawLine(SF->getRender()->getPresentationParameters()->BackBufferWidth / 2 + 28, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2 - 80, SF->getRender()->getPresentationParameters()->BackBufferWidth / 2 + 48, SF->getRender()->getPresentationParameters()->BackBufferHeight / 2 - 80, 1, -1);
		}

		if (ImGuiWindow->ImGuiDrawMenu) {
			if (LogFunc->log_enabled) {
				LogFunc->ShowExampleAppLog_(&LogFunc->show_app_log_);
			}
		}

		RenderBondage();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		SF->getRender()->EndRender();
	}
	return true;
}
//------------------\\

HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	return true;
}

bool __stdcall WndProcHandler(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hwd, msg, wParam, lParam);

	return true;
}