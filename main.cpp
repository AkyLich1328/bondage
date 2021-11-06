#include "main.h"

pFunc_ *pFunc = new pFunc_;
pool *pool_vehicle = new pool;
SAMPFUNCS *SF = new SAMPFUNCS();
stFontInfo *pFont = new stFontInfo;
ImGuiWindow_ *ImGuiWindow = new ImGuiWindow_;
CState_ *CState = new CState_;
BlockRPC_ *BlockRPC = new BlockRPC_;
LogFunc_ *LogFunc = new LogFunc_;
ExampleAppLog_ *ExampleAppLog = new ExampleAppLog_;
Collision_ *Collision = new Collision_;

void __stdcall testcmd(std::string params) {
	stInCarData data;
	memset(&data, 0, sizeof(stInCarData));
	memcpy(&data, &SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData, sizeof(stInCarData));

	data.sVehicleID = 14;
	data.fMoveSpeed[2] = 0.5;

	BitStream bsActorSync;
	bsActorSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsActorSync.Write((PCHAR)&data, sizeof(stInCarData));
	SF->getRakNet()->SendPacket(&bsActorSync);
}

void __stdcall PluginFree()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	ToggleCollisionHook(false);
}

void InitFunc(void) {
	SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Present);
	SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, Reset);
	SF->getGame()->registerWndProcCallback(SFGame::MEDIUM_CB_PRIORITY, WndProcHandler);
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	ImGui_ImplWin32_Init(GetActiveWindow());
	ImGui_ImplDX9_Init(SF->getRender()->getD3DDevice());
	SF->getGame()->registerGameDestructorCallback(PluginFree);
	pFont = SF->getRender()->CreateNewFont("Verdana", 12, FCR_BORDER);

	pFunc->Write((void*)(GetModuleHandle("samp.dll") + 0x5CF2C), "\x90\x90\x90\x90\x90", 5U);//анти краш от варнингов
	pFunc->Write((void*)(GetModuleHandle("samp.dll") + 0x5CF39), "\x90\x90\x90\x90\x90", 5U);

	ReadSettings();
	ToggleCollisionHook(true);
	if (ImGuiWindow->AntiHook)
		CState->SuperCollisionPatch(true);

	//RakNet
	SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_PACKET, incomingData);
	SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_PACKET, outcomingData);
	SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_INCOMING_RPC, incomingRPC);
	SF->getRakNet()->registerRakNetCallback(RakNetScriptHookType::RAKHOOK_TYPE_OUTCOMING_RPC, outcomingRPC);

	SF->getSAMP()->registerChatCommand("cmd", testcmd);

	SF->getSAMP()->getChat()->AddChatMessage(-1, "{808080}[{FF1493}AnaL{808080}.{FF1493}Bo[N]DaGe SF.Ed{808080}]{FF1493} Успешно загружен({808080}v3.0{808080})");
	SF->getSAMP()->getChat()->AddChatMessage(-1, "{808080}[{FF1493}AnaL{808080}.{FF1493}Bo[N]DaGe SF.Ed{808080}]{FF1493} Мой создатель: {808080}]GsH[MeG@LaDo[N]");
	SF->getSAMP()->getChat()->AddChatMessage(-1, "{808080}[{FF1493}AnaL{808080}.{FF1493}Bo[N]DaGe SF.Ed{808080}]{FF1493} Отдельное спасибо: {808080}]GsH[AdCKuY_DpO4uLa");
	SF->getSAMP()->getChat()->AddChatMessage(-1, "{808080}[{FF1493}AnaL{808080}.{FF1493}Bo[N]DaGe SF.Ed{808080}]{FF1493} Активация: {808080}F10");
}

void __stdcall mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			initialized = true;
			InitFunc();
		}
	}
	else {
		stuff();
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) {
		SF->initPlugin(mainloop, hModule);
		pFunc->cfgFile();
	}
	return TRUE;
}